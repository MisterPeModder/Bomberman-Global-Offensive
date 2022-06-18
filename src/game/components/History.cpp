/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Input History
*/

#include "History.hpp"

#include "ecs/Component.hpp"

#include <deque>
#include <string>

namespace game::components
{
    History::History(std::size_t pMaxSize) : maxSize(pMaxSize), pos(0) {}

    void History::push(std::string_view entry)
    {
        this->history.push_front(std::string(entry));
        if (this->history.size() > this->maxSize)
            this->history.pop_front();
        this->pos = 0;
    }

    void History::moveUp() { this->pos = std::min(this->pos + 1, this->history.size()); }

    void History::moveDown()
    {
        if (this->pos > 0)
            --this->pos;
    }

    std::string const &History::get() const noexcept
    {
        if (this->pos == 0 || this->pos > this->history.size())
            return this->savedCurrentEntry;
        else
            return this->history[this->pos - 1];
    }
} // namespace game::components
