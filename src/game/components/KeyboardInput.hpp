/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** KeyboardInput
*/

#ifndef GAME_COMPONENTS_INPUT_FIELD_HPP_
#define GAME_COMPONENTS_INPUT_FIELD_HPP_

#include "ecs/Component.hpp"

#include "raylib/core/Color.hpp"
#include "raylib/core/Keyboard.hpp"

#include "ecs/Entity.hpp"
#include "ecs/system/SystemData.hpp"

#include <array>
#include <functional>

namespace game
{
    /// Keyboard-only input field
    struct KeyboardInput : public ecs::Component {
        /// How the cursor should be drawn.
        enum class CursorType {
            NONE,
            BEAM,
        };

        /// Key repeat event data.
        class KeyRepeat {
          public:
            /// The minimum number of seconds between each character event repeat.
            static constexpr double REPEAT_DELAY = 0.025;
            /// The amount of seconds before the a key event starts repeating.
            static constexpr double REPEAT_THRESHOLD = 0.5;

            using Callback = std::function<void(KeyboardInput &, ecs::Entity, ecs::SystemData)>;

            KeyRepeat() = default;

            KeyRepeat(raylib::core::Keyboard::Key key, Callback callback);

            /// Executes the repeat callback if the key repeat cooldown is not active.
            ///
            /// @param input The keyboard input field.
            /// @param id The entity id of @b input.
            /// @param data System data.
            /// @param elapsed The number of seconds since the last call to KeyRepeat::check().
            void check(KeyboardInput &input, ecs::Entity id, ecs::SystemData data, double elapsed);

          private:
            raylib::core::Keyboard::Key _key;
            double _repeatCooldown;
            double _timeSinceRepeat;
            Callback _callback;
        };

        /// The type of function executed when the user presses the enter key while the input is focused.
        ///
        /// @param self the entity id of the input.
        /// @param data the system data.
        /// @param line the contents of the input field.
        ///
        /// @returns whether the input field should be cleared.
        using onSubmitCallback = std::function<bool(ecs::Entity, ecs::SystemData, std::string_view)>;

        onSubmitCallback onSubmit;

        std::string contents;
        std::size_t cursorPos;
        std::size_t selectionPos;

        /// Whether keyboard input should be captured.
        bool focused;

        /// Repeat support for some keys.
        std::array<KeyRepeat, 6> keyRepeats;

        double cursorBlink;

        KeyboardInput(onSubmitCallback submitCallback);

        /// Moves the cursor backwards or forwards of @b offset codepoints.
        void moveCursor(int offset, bool selectingText = false);

        /// Moves the cursor one word backwards or forwards.
        void moveCursorToWord(int wordOffset, bool selectingText = false);

        /// @returns The current cursor type.
        CursorType getCursorType();

        /// @returns Whether the input has selected text.
        bool hasSelection() noexcept;

        /// Deletes the selected text and resets the selection.
        void eraseSelection();

        /// Deletes the whole input.
        void clear();

        /// Executes the repeat event of each key in @ref keyRepeats.
        ///
        /// @param id The entity id this input.
        /// @param data System data.
        /// @param elapsed The number of seconds since the last call to KeyboardInput::checkKeyRepeats().
        void checkKeyRepeats(ecs::Entity id, ecs::SystemData data, double elapsed);
    };
} // namespace game

#endif // !defined(GAME_COMPONENTS_INPUT_FIELD_HPP_)
