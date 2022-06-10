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

from dataclasses import dataclass
import sys
import os
from typing import Iterator, List, Optional, TextIO, Tuple, OrderedDict


class JsType:
    def c_repr(self, name: str) -> str:
        return f"{self} {name}"

    def js_repr(self) -> str:
        return str(self)


@dataclass
class JsArg:
    type: JsType
    name: str

    def __str__(self) -> str:
        return self.type.c_repr(self.name)


@dataclass
class JsVoid(JsType):
    def __str__(self) -> str:
        return 'void'

    def js_repr(self) -> str:
        return 'undefined'


@dataclass
class JsNumber(JsType):
    def __str__(self) -> str:
        return 'bmjs::Number'

    def js_repr(self) -> str:
        return 'number'


@dataclass
class JsString(JsType):
    def __str__(self) -> str:
        return 'bmjs::String'

    def js_repr(self) -> str:
        return 'string'


@dataclass
class JsFunction(JsType):
    args: List[JsType]
    returns: JsType

    def __str__(self) -> str:
        args = ', '.join([str(arg) for arg in self.args])
        template_params = f"{self.returns}, {args}" if args != '' else str(
            self.returns)
        return f"bmjs::Function<{template_params}>"

    def js_repr(self) -> str:
        return 'number'

    def llvm_sig(self) -> str:
        if isinstance(self.returns, JsVoid):
            return 'v' + 'd' * len(self.args)
        return 'd' * (len(self.args) + 1)


@ dataclass(eq=True, order=True)
class Prototype:
    """JS C function prototype"""

    scope: str
    name: str
    raw_name: str
    args: List[JsArg]
    returns: JsType


def parse_type(input: str) -> Tuple[JsType, str]:
    input = input.lstrip()
    if input.startswith('void'):
        return (JsVoid(), input[4:])
    elif input.startswith('bmjs::Number'):
        return (JsNumber(), input[12:])
    elif input.startswith('bmjs::String'):
        return (JsString(), input[12:])
    elif input.startswith('bmjs::Function<'):
        return (JsFunction([], JsVoid()), input[15:])
    raise Exception(f"Unsupported type: {input}")


def parse_arg(input: str) -> Tuple[JsArg, str]:
    [type, input] = parse_type(input)
    input = input.lstrip()

    if isinstance(type, JsFunction):
        [template_params, input] = input.split('>', maxsplit=1)
        input = input.lstrip()
        args_str = template_params.split(',')

        type.returns, _ = parse_type(args_str[0])

        for arg_str in args_str[1:]:
            arg_type, _ = parse_type(arg_str)
            type.args.append(arg_type)

    name1 = input.split(',', maxsplit=1)[0]
    name2 = input.split(')', maxsplit=1)[0]
    if len(name1) < len(name2):
        return (JsArg(type, name1), input[len(name1) + 1:])
    else:
        return (JsArg(type, name2), input[len(name2):])


def read_prototype(line: str, lines: Iterator[str], scope: str) -> Optional[Prototype]:
    """Reads a function prototypes starting with BMJS_DEFINE."""

    if not line.startswith('BMJS_DEFINE'):
        return None
    while '{' not in line:
        next_line = next(lines, None)
        if next_line is None:
            break
        line += next_line.strip()
    prototype = line[11:].split('{')[0].strip()
    [returns_str, rest] = prototype.split(maxsplit=1)
    [raw_name, args_str] = rest.split(sep='(', maxsplit=1)

    returns, _ = parse_type(returns_str)

    args: List[JsArg] = []
    while args_str != ')':
        arg, args_str = parse_arg(args_str)
        args.append(arg)

    [function_scope, name] = raw_name.split('_', maxsplit=1)

    if function_scope != scope:
        print(
            f"warning: function {raw_name} is defined in the wrong scope {scope}", file=sys.stderr)

    return Prototype(scope, name, raw_name, args, returns)


def read_prototypes(lines: Iterator[str]) -> List[Prototype]:
    """Reads all functions prototypes starting with BMJS_DEFINE."""

    prototypes: List[Prototype] = []
    api_scope: str | None = None

    try:
        while line := next(lines):
            line = line.strip()

            if line.startswith('BMJS_API_START('):
                if api_scope is not None:
                    print(
                        'warning: succesive BMJS_API_START without BMJS_API_END', file=sys.stderr)
                api_scope = line[15:].split(')', maxsplit=1)[0]
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


def read_dir_prototypes(path: str) -> List[Prototype]:
    """Recursively reads all API prototypes in the given directory path"""

    prototypes: List[Prototype] = []

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
    args_str = ', '.join([str(arg) for arg in prototype.args])
    print(f"{prototype.returns} {prototype.raw_name}({args_str});", file=out)


def emit_function_prototypes(out: TextIO, prototypes: List[Prototype]) -> None:
    for prototype in prototypes:
        emit_function_prototype(out, prototype)
    print(file=out)


def emit_function_arg(out: TextIO, index: int, arg: JsArg, prototype: Prototype) -> None:
    if isinstance(arg.type, JsNumber):
        print(f"        {arg} = js_tonumber(state, {index});", file=out)
    elif isinstance(arg.type, JsString):
        print(f"        {arg} = js_tostring(state, {index});", file=out)
    elif isinstance(arg.type, JsFunction):
        registry_name = f"\"{prototype.scope}_{prototype.name}_callback\""
        lambda_args = ', '.join(
            [f"bmjs::Number {arg.name}_param_{i}" for i in range(len(arg.type.args))])

        print(f"""        js_copy(state, {index});
        js_setregistry(state, {registry_name});
        {arg} = [state]({lambda_args}) {{
            js_getregistry(state, {registry_name});
            js_pushundefined(state);""", file=out)

        for i in range(len(arg.type.args)):
            print(
                f"            js_pushnumber(state, {arg.name}_param_{i});", file=out)

        print(f"""
            if (js_pcall(state, {len(arg.type.args)})) {{
                bmjs::JsException error(js_tostring(state, -1));
                js_pop(state, 1);
                throw error;
            }}""", file=out)

        if isinstance(arg.type.returns, JsNumber):
            print(f"""
            {arg.type.returns.c_repr('result')} = js_tonumber(state, -1);
            js_pop(state, 1);
            return result;
        }};""", file=out)
        else:
            print(f"""
            js_pop(state, 1);
        }};""", file=out)


def emit_function_args(out: TextIO, prototype: Prototype) -> None:
    for i, arg in enumerate(prototype.args):
        emit_function_arg(out, i + 1, arg, prototype)
    if prototype.args != []:
        print(file=out)


def emit_function_call(out: TextIO, prototype: Prototype) -> None:
    args_str = ', '.join([arg.name for arg in prototype.args])

    if isinstance(prototype.returns, JsVoid):
        print(f"        ::{prototype.raw_name}({args_str});", file=out)
    else:
        print(
            f"        {prototype.returns} result = ::{prototype.raw_name}({args_str});", file=out)


def emit_function_result(out: TextIO, prototype: Prototype) -> None:
    if isinstance(prototype.returns, JsVoid):
        print("        js_pushundefined(state);", file=out)
    elif isinstance(prototype.returns, JsNumber):
        print("        js_pushnumber(state, result);", file=out)
    elif isinstance(prototype.returns, JsString):
        print("        js_pushstring(state, result);", file=out)


def emit_function(out: TextIO, prototype: Prototype) -> None:
    print(
        f"    static void {prototype.raw_name}_mujs(js_State *state)", file=out)
    print('    {', file=out)
    emit_function_args(out, prototype)
    emit_function_call(out, prototype)
    emit_function_result(out, prototype)
    print('    }', file=out)


def emit_functions(out: TextIO, prototypes: List[Prototype]) -> None:
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


def emit_scope_registration(out: TextIO, scope: str, prototypes: List[Prototype]) -> None:
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
    }}
""", file=out)


def emit_register_functions(out: TextIO, scopes: OrderedDict[str, List[Prototype]]) -> None:
    print("""namespace bmjs
{""", file=out)

    for scope, prototypes in scopes.items():
        emit_scope_registration(out, scope, prototypes)

    print("""    /// Registers the JS bindings in the 'bm' global object.
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


def emit_cxx_bindings(out: TextIO, prototypes: List[Prototype], scopes: OrderedDict[str, List[Prototype]]) -> None:

    print("""/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Generated File
*/

// clang-format on

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
# ifndef __EMSCRIPTEN__
    # include "script/JsException.hpp"
    # include "script/script.hpp"
""", file=out)

    emit_function_prototypes(out, prototypes)
    emit_functions(out, prototypes)
    emit_register_functions(out, scopes)

    print("""#endif // !defined(__EMSCRIPTEN__)

// clang-format off""", file=out)


def emit_js_scope_binding(out: TextIO, prototype: Prototype, terminator: str = '') -> None:
    arg_types = ', '.join(
        [f"'{arg.type.js_repr()}'" for arg in prototype.args])
    definition = f"'{prototype.raw_name}', '{prototype.returns.js_repr()}', [{arg_types}]"

    print(f"        {prototype.name}: ", file=out, end='')

    if any([isinstance(arg.type, JsFunction) for arg in prototype.args]):
        params = ', '.join([arg.name for arg in prototype.args])
        call_args: List[str] = []

        for arg in prototype.args:
            if isinstance(arg.type, JsFunction):
                call_args.append(
                    f"addFunction({arg.name}, '{arg.type.llvm_sig()}')")
            else:
                call_args.append(arg.name)

        print(f"""function ({params}) {{
            return ccall({definition}, [{', '.join(call_args)}]);
        }}{terminator}""", file=out)
    else:
        print(f"cwrap({definition}){terminator}", file=out)


def emit_js_scope_bindings(out: TextIO, scope: str, prototypes: List[Prototype]) -> None:
    print(f"    bm.{scope} = {{", file=out)

    for prototype in prototypes[:-1]:
        emit_js_scope_binding(out, prototype, ',')
    if prototypes != []:
        emit_js_scope_binding(out, prototypes[-1])

    print('    };', file=out)


def emit_js_bindings(out: TextIO, scopes: OrderedDict[str, List[Prototype]]) -> None:
    print("""/**
 * @file Browser bindings generated by 'generate_bindings.py', DO NOT EDIT!
 */

var bm;

(function (bm) {""", file=out)

    for scope, prototypes in scopes.items():
        emit_js_scope_bindings(out, scope, prototypes)

    print('})(bm || (bm = {}));', file=out)


def main(args: List[str]) -> None:
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

    scopes: OrderedDict[str, List[Prototype]] = OrderedDict()
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
