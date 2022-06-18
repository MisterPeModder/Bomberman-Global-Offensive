/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Keyboard
*/

#ifndef RAYLIB_CORE_KEYBOARD_HPP_
#define RAYLIB_CORE_KEYBOARD_HPP_

extern "C"
{
#include <raylib.h>
}

namespace raylib
{
    namespace core
    {
        class Keyboard {
          public:
            enum class Key {
                NONE = 0, //< NONE, used for no key pressed
                // Alphanumeric keys
                APOSTROPHE = 39,    //< '
                COMMA = 44,         //< ,
                MINUS = 45,         //< -
                PERIOD = 46,        //< .
                SLASH = 47,         //< /
                ZERO = 48,          //< 0
                ONE = 49,           //< 1
                TWO = 50,           //< 2
                THREE = 51,         //< 3
                FOUR = 52,          //< 4
                FIVE = 53,          //< 5
                SIX = 54,           //< 6
                SEVEN = 55,         //< 7
                EIGHT = 56,         //< 8
                NINE = 57,          //< 9
                SEMICOLON = 59,     //< ;
                EQUAL = 61,         //< =
                A = 65,             //< A | a
                B = 66,             //< B | b
                C = 67,             //< C | c
                D = 68,             //< D | d
                E = 69,             //< E | e
                F = 70,             //< F | f
                G = 71,             //< G | g
                H = 72,             //< H | h
                I = 73,             //< I | i
                J = 74,             //< J | j
                K = 75,             //< K | k
                L = 76,             //< L | l
                M = 77,             //< M | m
                N = 78,             //< N | n
                O = 79,             //< O | o
                P = 80,             //< P | p
                Q = 81,             //< Q | q
                R = 82,             //< R | r
                S = 83,             //< S | s
                T = 84,             //< T | t
                U = 85,             //< U | u
                V = 86,             //< V | v
                W = 87,             //< W | w
                X = 88,             //< X | x
                Y = 89,             //< Y | y
                Z = 90,             //< Z | z
                LEFT_BRACKET = 91,  //< [
                BACKSLASH = 92,     //< '\'
                RIGHT_BRACKET = 93, //< ]
                GRAVE = 96,         //< `
                // Function keys
                SPACE = 32,          //< Space
                ESCAPE = 256,        //< Esc
                ENTER = 257,         //< Enter
                TAB = 258,           //< Tab
                BACKSPACE = 259,     //< Backspace
                INSERT = 260,        //< Ins
                DELETE = 261,        //< Del
                RIGHT = 262,         //< Cursor right
                LEFT = 263,          //< Cursor left
                DOWN = 264,          //< Cursor down
                UP = 265,            //< Cursor up
                PAGE_UP = 266,       //< Page up
                PAGE_DOWN = 267,     //< Page down
                HOME = 268,          //< Home
                END = 269,           //< End
                CAPS_LOCK = 280,     //< Caps lock
                SCROLL_LOCK = 281,   //< Scroll down
                NUM_LOCK = 282,      //< Num lock
                PRINT_SCREEN = 283,  //< Print screen
                PAUSE = 284,         //< Pause
                F1 = 290,            //< F1
                F2 = 291,            //< F2
                F3 = 292,            //< F3
                F4 = 293,            //< F4
                F5 = 294,            //< F5
                F6 = 295,            //< F6
                F7 = 296,            //< F7
                F8 = 297,            //< F8
                F9 = 298,            //< F9
                F10 = 299,           //< F10
                F11 = 300,           //< F11
                F12 = 301,           //< F12
                LEFT_SHIFT = 340,    //< Shift left
                LEFT_CONTROL = 341,  //< Control left
                LEFT_ALT = 342,      //< Alt left
                LEFT_SUPER = 343,    //< Super left
                RIGHT_SHIFT = 344,   //< Shift right
                RIGHT_CONTROL = 345, //< Control right
                RIGHT_ALT = 346,     //< Alt right
                RIGHT_SUPER = 347,   //< Super right
                KB_MENU = 348,       //< KB menu
                // Keypad keys
                KP_0 = 320,        //< Keypad 0
                KP_1 = 321,        //< Keypad 1
                KP_2 = 322,        //< Keypad 2
                KP_3 = 323,        //< Keypad 3
                KP_4 = 324,        //< Keypad 4
                KP_5 = 325,        //< Keypad 5
                KP_6 = 326,        //< Keypad 6
                KP_7 = 327,        //< Keypad 7
                KP_8 = 328,        //< Keypad 8
                KP_9 = 329,        //< Keypad 9
                KP_DECIMAL = 330,  //< Keypad .
                KP_DIVIDE = 331,   //< Keypad /
                KP_MULTIPLY = 332, //< Keypad *
                KP_SUBTRACT = 333, //< Keypad -
                KP_ADD = 334,      //< Keypad +
                KP_ENTER = 335,    //< Keypad Enter
                KP_EQUAL = 336,    //< Keypad =
                // Android key buttons
                BACK = 4,        //< Android back button
                MENU = 82,       //< Android menu button
                MUSIC_VOLUME_UP = 24,  //< Android volume up button
                MUSIC_VOLUME_DOWN = 25 //< Android volume down button
            };

            /// Check if a key has been pressed once.
            ///
            /// @param key key to check.
            /// @return true If the key has been pressed.
            static bool isKeyPressed(Key key);

            /// Check if a key is being pressed.
            ///
            /// @param key key to check.
            /// @return true If the key is pressed.
            static bool isKeyDown(Key key);

            /// Check if a key has been released once.
            ///
            /// @param key key to check.
            /// @return true If the key has been released.
            static bool isKeyReleased(Key key);

            /// Check if a key is NOT being pressed.
            ///
            /// @param key key to check.
            /// @return true If the key is not pressed.
            static bool isKeyUp(Key key);

            /// Set a custom key to exit program (default is ESC)
            ///
            /// @param key key bind to the exit of the program.
            static void setExitKey(Key key);

            /// Get key pressed, call it multiple times for keys queued, returns Key::NONE when the queue is empty
            ///
            /// @return Key key pressed
            ///
            static Key getKeyPressed();

            /// Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
            ///
            /// @return int unicode character pressed, 0 when the queue is empty.
            static int getCharPressed();

          private:
            Keyboard();
            ~Keyboard();
        };
    } // namespace core
} // namespace raylib

#endif /* !RAYLIB_CORE_KEYBOARD_HPP_ */
