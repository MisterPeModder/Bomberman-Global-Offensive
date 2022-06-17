/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Input History
*/

#ifndef GAME_COMPONENTS_HISTORY
#define GAME_COMPONENTS_HISTORY

#include "ecs/Component.hpp"

#include <deque>
#include <string>
#include <string_view>

namespace game::components
{
    /// An history of string entries.
    struct History : public ecs::Component {
        /// Saved history entries, from newest to oldest.
        std::deque<std::string> history;

        /// The maximum number of entries in the history.
        std::size_t maxSize;

        /// The position in history, 0 means the current entry, saved entries starts at index 1.
        std::size_t pos;

        /// The current entry, not in history.
        std::string savedCurrentEntry;

        /// @param pMaxSize The maximum number of entry in the history.
        History(std::size_t pMaxSize = 50);

        /// Adds a new history entry.
        void push(std::string_view entry);

        /// Move one entry up.
        void moveUp();

        /// Move one entry down.
        void moveDown();

        /// Loads the selected entry into @b dst.
        void load(std::string &dst);
    };
} // namespace game::components

#endif // !defined(GAME_COMPONENTS_HISTORY)
