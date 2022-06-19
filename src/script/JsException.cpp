/*
** EPITECH PROJECT, 2022
** bomberman: global offensive
** File description:
** JsException
*/

#include "JsException.hpp"

namespace bmjs
{
    JsException::JsException(std::string_view message) : std::runtime_error(message.data()) {}
} // namespace bmjs
