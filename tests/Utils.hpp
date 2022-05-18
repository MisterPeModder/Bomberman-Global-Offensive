/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** exception_check
*/

#ifndef INDIE_EXCEPTION_CHECK_HPP_
#define INDIE_EXCEPTION_CHECK_HPP_

#include <functional>
#include <stdexcept>

///
/// Execute a function in a tryBlock expecting a specific exception.
///
/// @tparam Exception expected exception.
/// @param tryBlock function to execute.
/// @return true If the @c Exception was throwed.
/// @return false If an other std::exception was throwed, or if no exception were throwed.
template <typename Exception>
requires std::derived_from<Exception, std::exception>
bool isException(std::function<void(void)> tryBlock)
{
    try {
        tryBlock();
        return false;
    } catch (Exception &) {
        return true;
    } catch (std::exception &) {
        return false;
    }
    return false;
}

#endif /* !INDIE_EXCEPTION_CHECK_HPP_ */
