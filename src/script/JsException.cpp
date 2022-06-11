/*
** EPITECH PROJECT, 2022
** bomberman: global offensive
** File description:
** JsException
*/

#include "JsException.hpp"

namespace bmjs
{
    JsException::JsException(char const *message) : std::runtime_error(message) {}
} // namespace bmjs
