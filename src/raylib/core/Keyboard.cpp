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
        bool Keyboard::isKeyPressed(Key key) { return ::IsKeyPressed(static_cast<int>(key)); }

        bool Keyboard::isKeyDown(Key key) { return ::IsKeyDown(static_cast<int>(key)); }

        bool Keyboard::isKeyReleased(Key key) { return ::IsKeyReleased(static_cast<int>(key)); }

        bool Keyboard::isKeyUp(Key key) { return ::IsKeyUp(static_cast<int>(key)); }

        void Keyboard::setExitKey(Key key) { ::SetExitKey(static_cast<int>(key)); }

        Keyboard::Key Keyboard::getKeyPressed() { return static_cast<Key>(::GetKeyPressed()); }

        int Keyboard::getCharPressed() { return ::GetCharPressed(); }
    } // namespace core
} // namespace raylib