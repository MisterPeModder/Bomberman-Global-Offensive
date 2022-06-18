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
#include "raylib/core/Vector2.hpp"

#include "ecs/Entity.hpp"
#include "ecs/system/SystemData.hpp"

#include <array>
#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace game::components
{
    class History;

    /// Keyboard-only input field
    class KeyboardInput : public ecs::Component {
      public:
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

        std::vector<std::string> contents;

        raylib::core::Vector2u cursorPos;
        raylib::core::Vector2u selectionPos;

        /// Whether keyboard input should be captured.
        bool focused;

        /// Repeat support for some keys.
        std::array<KeyRepeat, 6> keyRepeats;

        double cursorBlink;

        KeyboardInput(onSubmitCallback submitCallback);

        /// @returns A pair of vectors corresponding to the start and the end of the selection, respectively.
        std::pair<raylib::core::Vector2u, raylib::core::Vector2u> getSelection() const noexcept;

        /// Moves the cursor backwards or forwards of @b offset codepoints.
        ///
        /// @param selectingText Whether the user is in selection mode.
        void moveCursor(int offset, bool selectingText = false);

        /// Moves the cursor one word backwards or forwards.
        ///
        /// @param selectingText Whether the user is in selection mode.
        void moveCursorToWord(int wordOffset, bool selectingText = false);

        /// Sets the cursor at a specific position.
        ///
        /// @param pos The new cursor position, it will be adjusted for UTF-8 borders
        /// @param selectingText Whether the user is in selection mode.
        void setCursorPos(raylib::core::Vector2u pos, bool selectingText = false) noexcept;

        /// @returns The current cursor type.
        CursorType getCursorType();

        /// @returns Whether the input has selected text.
        bool hasSelection() const noexcept;

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

        /// Merges all the content lines into a single string seperated by '\n'
        ///
        /// @returns The merged contents.
        std::string mergeContents() const;

        /// Loads a newline-seprated string into the content.
        ///
        /// @param merged A merged string.
        void unmergeContents(std::string_view merged);

        /// Selects all the content.
        void selectAll();

        /// Copies the current selection to the system clipboard.
        ///
        /// @param doCut Whether to erase the selection after copying.
        void copyToClipboard(bool doCut);

        /// Paste the contents of the system clipboard at the current cursor position.
        void pasteFromClipboard();

        /// Inserts a new line at the cursor's position.
        void insertLine();

        /// Process the contents
        void submit(ecs::Entity self, ecs::SystemData data, game::components::History *history);

        /// @returns Whether the left or left shift keys are pressed.
        static bool selectKeyDown();

      private:
        /// Deletes the character to the left of the cursor.
        void deleteBackwards();

        /// Deletes the character to the right of the cursor.
        void deleteForwards();

        /// Loads the previous histrory entry.
        void prevHistory(History &History);

        /// Loads the next histrory entry.
        void nextHistory(History &History);
    };
} // namespace game::components

#endif // !defined(GAME_COMPONENTS_INPUT_FIELD_HPP_)
