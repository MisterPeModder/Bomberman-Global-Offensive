/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** JsException
*/

#ifndef SCRIPT_JS_EXCEPTION_HPP_
#define SCRIPT_JS_EXCEPTION_HPP_

#include <stdexcept>
#include <string_view>

namespace bmjs
{
    /// Exception thrown by invocations of bmjs::Function.
    class JsException : public std::runtime_error {
      public:
        JsException(std::string_view message);
    };
} // namespace bmjs

#endif // !defined(SCRIPT_JS_EXCEPTION_HPP_)
