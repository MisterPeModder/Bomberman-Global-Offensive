/*
** EPITECH PROJECT, 2022
** IndieStudio
** File description:
** RegistryGuard
*/

#if !defined(SCRIPT_REGISTRY_GUARD_HPP_) && !defined(__EMSCRIPTEN__)
    #define SCRIPT_REGISTRY_GUARD_HPP_

    #include <mujs.h>
    #include <string>

namespace bmjs
{
    /// Watches a value stored in the MuJS registry.
    class RegistryGuard {
      public:
        /// Default constructor.
        RegistryGuard();

        /// Pops the top value from the stack and adds it to the registry with a unique name.
        ///
        /// @param state The JS state, must not be nullptr.
        RegistryGuard(js_State *state);

        /// Cannot copy RegistryGuard, a registry value should be unique.
        RegistryGuard(RegistryGuard const &) = delete;

        /// Move constructor.
        RegistryGuard(RegistryGuard &&) noexcept;

        /// Destructor.
        ~RegistryGuard();

        /// @returns The id of the value created in the guard's constructor.
        constexpr std::string const &getKey() const noexcept { return this->_key; }

      private:
        js_State *_state;
        std::string _key;
    };
} // namespace bmjs

#endif // !defined(SCRIPT_REGISTRY_GUARD_HPP_) && !defined(__EMSCRIPTEN__)
