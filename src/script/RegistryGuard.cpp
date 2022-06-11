/*
** EPITECH PROJECT, 2022
** IndieStudio
** File description:
** RegistryGuard
*/

#if !defined(__EMSCRIPTEN__)

    #include "RegistryGuard.hpp"

    #include <mujs.h>
    #include <string>
    #include <utility>

namespace bmjs
{
    RegistryGuard::RegistryGuard() : _state(nullptr), _key() {}

    RegistryGuard::RegistryGuard(js_State *state) : _state(state), _key(js_ref(state)) {}

    RegistryGuard::RegistryGuard(RegistryGuard &&other) noexcept : _state(other._state), _key(std::move(other._key))
    {
        other._state = nullptr;
    }

    RegistryGuard::~RegistryGuard()
    {
        if (this->_state != nullptr)
            js_unref(this->_state, this->_key.c_str());
    }
} // namespace bmjs

#endif // !defined(__EMSCRIPTEN__)
