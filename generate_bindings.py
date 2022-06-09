#!/usr/bin/env python3

"""A tool that generates C++ to JS bindings for both Emscripten and MuJS.

Usage:
  generate_bindings API_DIRECTORY CXX_OUTPUT_FILE JS_OUTPUT_FILE

  API_DIRECTORY   The directory with files containing BM_API_START calls.
  CXX_OUTPUT_FILE The generated C++ output file.
  JS_OUTPUT_FILE  The generated JS output file.

Example:
  ./generate_bindings.py src/script/api/ src/script/bindings.cpp src/script/bindings.js
"""

from collections import OrderedDict
from dataclasses import dataclass
import sys
import os
from typing import Iterator, TextIO


@dataclass(eq=True, order=True)
class Prototype:
    """JS C function prototype"""

    name: str
    raw_name: str
    args: list[tuple[str, str]]
    returns: str
    scope: str


def read_prototype(line: str, lines: Iterator[str], scope: str) -> Prototype | None:
    """Reads a function prototypes starting with BMJS_DEFINE."""

    if not line.startswith('BMJS_DEFINE'):
        return None
    while '{' not in line:
        next_line = next(lines, None)
        if next_line is None:
            break
        line += next_line.strip()
    prototype = line.removeprefix('BMJS_DEFINE').split('{')[0].strip()
    [returns, rest] = prototype.split(maxsplit=1)
    [raw_name, args_str] = rest.split(sep='(', maxsplit=1)
    args_str = args_str[:-1]

    args: list[tuple[str, str]] = []

    if args_str != '':
        for arg_str in args_str.split(','):
            type_and_name = arg_str.split()
            args.append((type_and_name[0], type_and_name[1]))

    [function_scope, name] = raw_name.split('_', maxsplit=1)

    if function_scope != scope:
        print(
            f"warning: function {raw_name} is defined in the wrong scope {scope}", file=sys.stderr)

    return Prototype(name, raw_name, args, returns, scope)


def read_prototypes(lines: Iterator[str]) -> list[Prototype]:
    """Reads all functions prototypes starting with BMJS_DEFINE."""

    prototypes: list[Prototype] = []
    api_scope: str | None = None

    try:
        while line := next(lines):
            line = line.strip()

            if line.startswith('BMJS_API_START('):
                if api_scope is not None:
                    print(
                        'warning: succesive BMJS_API_START without BMJS_API_END', file=sys.stderr)
                api_scope = line.removeprefix(
                    'BMJS_API_START(').split(')', maxsplit=1)[0]
            elif line == 'BMJS_API_END':
                if api_scope is None:
                    print(
                        'warning: BMJS_API_END without correspoding BMJS_API_START', file=sys.stderr)
                api_scope = None
            elif api_scope is not None and (prototype := read_prototype(line, lines, api_scope)) is not None:
                prototypes.append(prototype)

    except StopIteration:
        return prototypes
    return prototypes


def read_dir_prototypes(path: str) -> list[Prototype]:
    """Recursively reads all API prototypes in the given directory path"""

    prototypes: list[Prototype] = []

    for file in os.listdir(path):
        sub_path = os.path.join(path, file)
        if os.path.isdir(sub_path):
            prototypes += read_dir_prototypes(sub_path)
        elif sub_path.endswith('.cpp'):
            with open(sub_path) as input:
                print(f"Reading prototypes of {sub_path}")
                prototypes += read_prototypes(iter(input))
    return prototypes


def emit_function_prototype(out: TextIO, prototype: Prototype) -> None:
    args_str = ', '.join([f"{name} {type}" for (name, type) in prototype.args])
    print(
        f"    {prototype.returns} {prototype.raw_name}({args_str});", file=out)


def emit_function_prototypes(out: TextIO, prototypes: list[Prototype]) -> None:
    print('extern "C"', file=out)
    print('{', file=out)

    for prototype in prototypes:
        emit_function_prototype(out, prototype)

    print('}', file=out)
    print(file=out)


def emit_function_arg(out: TextIO, index: int, type: str, name: str) -> None:
    print(f"        {type} {name} = ", end='', file=out)
    match (type):
        case 'bmjs::Number':
            print(f"js_tonumber(state, {index});", file=out)
        case 'bmjs::String':
            print(f"js_tostring(state, {index});", file=out)


def emit_function_args(out: TextIO, prototype: Prototype) -> None:
    for i, (type, name) in enumerate(prototype.args):
        emit_function_arg(out, i + 1, type, name)
    if prototype.args != []:
        print(file=out)


def emit_function_call(out: TextIO, prototype: Prototype) -> None:
    args_str = ', '.join([name for (_, name) in prototype.args])

    if prototype.returns == 'void':
        print(f"        ::{prototype.raw_name}({args_str});", file=out)
    else:
        print(
            f"        {prototype.returns} result = ::{prototype.raw_name}({args_str});", file=out)


def emit_function_result(out: TextIO, prototype: Prototype) -> None:
    match (prototype.returns):
        case 'void':
            print("        js_pushundefined(state);", file=out)
        case 'bmjs::Number':
            print("        js_pushnumber(state, result);", file=out)
        case 'bmjs::String':
            print("        js_pushstring(state, result);", file=out)


def emit_function(out: TextIO, prototype: Prototype) -> None:
    print(
        f"    static void {prototype.raw_name}_mujs(js_State *state)", file=out)
    print('    {', file=out)
    emit_function_args(out, prototype)
    emit_function_call(out, prototype)
    emit_function_result(out, prototype)
    print('    }', file=out)


def emit_functions(out: TextIO, prototypes: list[Prototype]) -> None:
    print('extern "C"', file=out)
    print('{', file=out)

    if prototypes != []:
        emit_function(out, prototypes[0])
    for prototype in prototypes[1:]:
        print(file=out)
        emit_function(out, prototype)

    print('}', file=out)
    print(file=out)


def emit_scope(out: TextIO, prototype: Prototype) -> None:
    print(f"""
        js_newcfunction(state, &::{prototype.name}_mujs, \"{prototype.name}\", {len(prototype.args)});
        js_setglobal(state, \"{prototype.name}\");""", file=out)


def emit_scope_registration(out: TextIO, scope: str, prototypes: list[Prototype]) -> None:
    print(f"""    /// Registers the functions in the {scope} group.
    static void registerMuJSBindings_{scope}(js_State *state)
    {{
        js_newobject(state);""", file=out)

    for prototype in prototypes:
        print(f"""
        js_newcfunction(state, &::{prototype.raw_name}_mujs, \"{prototype.name}\", {len(prototype.args)});
        js_setproperty(state, -2, \"{prototype.name}\");""", file=out)
    print(f"""
        js_setproperty(state, -2, \"{scope}\");
    }}""", file=out)


def emit_register_functions(out: TextIO, scopes: OrderedDict[str, list[Prototype]]) -> None:
    print("""namespace bmjs
{""", file=out)

    for scope, prototypes in scopes.items():
        emit_scope_registration(out, scope, prototypes)

    print("""
    /// Registers the JS bindings in the 'bm' global object.
    void registerMuJSBindings(js_State *state)
    {
        js_newobject(state);
""", file=out)

    for scope in scopes.keys():
        print(f"        registerMuJSBindings_{scope}(state);", file=out)

    print("""
        js_setglobal(state, \"bm\");
    }
} // namespace bmjs
""", file=out)


def emit_cxx_bindings(out: TextIO, prototypes: list[Prototype], scopes: OrderedDict[str, list[Prototype]]) -> None:

    print("""/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Generated File
*/

/// @file
/// @internal
///
/// MuJS Bindings generated by 'generate_bindings.py'
/// DO NOT EDIT!
///
/// Available groups:""", file=out)

    if len(scopes) == 0:
        print('/// (none)', file=out)
    for scope, protos in scopes.items():
        print(f"/// - {scope} ({len(protos)} functions)", file=out)

    print("""
#ifndef __EMSCRIPTEN__
    #include "script/script.hpp"
""", file=out)

    emit_function_prototypes(out, prototypes)
    emit_functions(out, prototypes)
    emit_register_functions(out, scopes)

    print("""#endif // !defined(__EMSCRIPTEN__)""", file=out)


def to_js_type(type: str) -> str:
    match (type):
        case 'bmjs::Number': return "'number'"
        case 'bmjs::String': return "'string'"
        case _: return "'undefined'"


def emit_js_scope_binding(out: TextIO, prototype: Prototype, terminator: str = '') -> None:
    args = ", ".join([to_js_type(type) for type, _ in prototype.args])
    print(
        f"        {prototype.name}: cwrap('{prototype.raw_name}', {to_js_type(prototype.returns)}, [{args}]){terminator}", file=out)


def emit_js_scope_bindings(out: TextIO, scope: str, prototypes: list[Prototype]) -> None:
    print(f"    bm.{scope} = {{", file=out)

    for prototype in prototypes[:-1]:
        emit_js_scope_binding(out, prototype, ',')
    if prototypes != []:
        emit_js_scope_binding(out, prototypes[-1])

    print('    };', file=out)
    pass


def emit_js_bindings(out: TextIO, scopes: OrderedDict[str, list[Prototype]]) -> None:
    print("""/**
 * @file Browser bindings generated by 'generate_bindings.py', DO NOT EDIT!
 */

var bm;

(function (bm) {""", file=out)

    for scope, prototypes in scopes.items():
        emit_js_scope_bindings(out, scope, prototypes)

    print('})(bm || (bm = {}));', file=out)


def main(args: list[str]) -> None:
    if len(args) != 4:
        message = f"USAGE: {args[0]} API_DIRECTORY CXX_OUTPUT_FILE JS_OUTPUT_FILE"
        if len(args) == 2 and (args[1] == '-h' or args[1] == '--help'):
            print(message)
            return
        raise Exception(message)

    if not os.path.isdir(args[1]):
        raise Exception(f"{args[1]}: not a directory")

    prototypes = read_dir_prototypes(args[1])
    prototypes.sort()

    scopes: OrderedDict[str, list[Prototype]] = OrderedDict()
    for prototype in prototypes:
        if prototype.scope in scopes:
            scopes[prototype.scope].append(prototype)
        else:
            scopes[prototype.scope] = [prototype]

    print('Generating bindings...')
    with open(args[2], mode='w') as out:
        emit_cxx_bindings(out, prototypes, scopes)

    with open(args[3], mode='w') as out:
        emit_js_bindings(out, scopes)


if __name__ == "__main__":
    try:
        main(sys.argv)
    except Exception as err:
        print(err, file=sys.stderr)
        sys.exit(1)
