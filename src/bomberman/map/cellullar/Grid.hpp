/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Grid
*/

#ifndef BOMBERMAN_MAP_CELLULAR_GRID_HPP_
#define BOMBERMAN_MAP_CELLULAR_GRID_HPP_

#include <vector>
#include "Rule.hpp"

namespace bomberman
{
    namespace map
    {
        namespace cellular
        {
            class Grid {
              public:
                Grid(size_t width = 1, size_t height = 1);
                ~Grid() = default;

                void generate(Rule &rule, size_t fillPercent = 60);
                void generate(size_t fillPercent = 60);
                void clear();
                void randomFill(size_t fillPercent);
                void iterate();

                const std::vector<bool> &getGrid() const;

                void setRule(Rule &rule);
                const Rule &getRule() const;

                bool at(size_t x, size_t y) const;

                void setSize(size_t width, size_t height);

              private:
                bool isFilled(int x, int y) const;
                unsigned char getNeighbours(size_t x, size_t y) const;

                size_t _width;
                size_t _height;
                std::vector<bool> _cells;
                Rule _rule;
            };
        } // namespace cellular
    }     // namespace map
} // namespace bomberman

#endif /* !BOMBERMAN_MAP_CELLULAR_GRID_HPP_ */
