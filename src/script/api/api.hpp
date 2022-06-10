/*
** EPITECH PROJECT, 2022
** IndieStudio
** File description:
** Bomberman JS API declarations
*/

#ifndef SCRIPT_API_API_HPP_
#define SCRIPT_API_API_HPP_

#include "script/script.hpp"

BMJS_DECLARE_API(common)
BMJS_DECLARE_API(mods)

namespace bmjs
{
    /// Forces Emscripten to not remove the API functions from the binary.
    inline void useApis()
    {
        BMJS_USE_API(common);
        BMJS_USE_API(mods);
    }
} // namespace bmjs

#endif // !defined(SCRIPT_API_API_HPP_)
