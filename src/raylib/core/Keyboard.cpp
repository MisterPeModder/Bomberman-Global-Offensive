/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Keyboard
*/

#include "Keyboard.hpp"

namespace raylib
{
    namespace core
    {
        bool Keyboard::IsKeyPressed(Key key) { return ::IsKeyPressed(static_cast<int>(key)); }

        bool Keyboard::IsKeyDown(Key key) { return ::IsKeyDown(static_cast<int>(key)); }

        bool Keyboard::IsKeyReleased(Key key) { return ::IsKeyReleased(static_cast<int>(key)); }

        bool Keyboard::IsKeyUp(Key key) { return ::IsKeyUp(static_cast<int>(key)); }

        void Keyboard::SetExitKey(Key key) { ::SetExitKey(static_cast<int>(key)); }

        Keyboard::Key Keyboard::GetKeyPressed(void) { return static_cast<Key>(::GetKeyPressed()); }

        int Keyboard::GetCharPressed(void) { return ::GetCharPressed(); }
    } // namespace core
} // namespace raylib