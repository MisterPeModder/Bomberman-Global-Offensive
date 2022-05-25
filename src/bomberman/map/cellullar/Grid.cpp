/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Grid
*/

#include "Grid.hpp"
#include <iterator>
#include <random>
#include <stdexcept>

namespace bomberman
{
    namespace map
    {
        namespace cellular
        {
            Grid::Grid(size_t width, size_t height) { setSize(width, height); }

            void Grid::generate(Rule &rule, size_t fillPercent)
            {
                setRule(rule);
                generate(fillPercent);
            }

            void Grid::generate(size_t fillPercent) { randomFill(fillPercent); }

            void Grid::clear() { std::fill(_cells.begin(), _cells.end(), false); }

            void Grid::randomFill(size_t fillPercent)
            {
                if (fillPercent > 100)
                    throw std::logic_error("Grid cannot be filled more than 100%."); /// Replace with custom exception
                std::random_device dev;
                std::mt19937 rng(dev());
                std::uniform_int_distribution<std::mt19937::result_type> dist100(0, 99);

                clear();
                if (fillPercent > 0)
                    std::for_each(_cells.begin(), _cells.end(), [&](auto cell) { cell = dist100(rng) < fillPercent; });
            }

            void Grid::iterate()
            {
                std::vector<bool> newState = _cells;

                for (size_t x = 0; x < _width; x++)
                    for (size_t y = 0; y < _height; y++)
                        newState[x + y * _width] = _rule.nextState(getNeighbours(x, y), at(x, y));
                std::copy(newState.begin(), newState.end(), std::back_inserter(_cells));
            }

            const std::vector<bool> &Grid::getGrid() const { return _cells; }

            void Grid::setRule(Rule &rule) { _rule = rule; }

            const Rule &Grid::getRule() const { return _rule; }

            bool Grid::at(size_t x, size_t y) const
            {
                if (x >= _width || y >= _height)
                    throw std::out_of_range("Accessing out of bounds map element."); /// Replace with custom exception
                return _cells[x + y * _width];
            }

            void Grid::setSize(size_t width, size_t height)
            {
                _width = width;
                _height = height;
                _cells.resize(_width * _height);
            }

            bool Grid::isFilled(int x, int y) const
            {
                if (x == -1 || y == -1 || x == _width || y == _width)
                    return false;
                return at(x, y);
            }

            unsigned char Grid::getNeighbours(size_t x, size_t y) const
            {
                unsigned char nbNeighbours = 0;

                for (int tempX = static_cast<int>(x) - 1; tempX < x + 2; tempX++)
                    for (int tempY = static_cast<int>(y) - 1; tempY < y + 2; tempY++) {
                        if (tempX == x && tempY == y)
                            continue;
                        nbNeighbours += isFilled(tempX, tempY);
                    }
                return nbNeighbours;
            }
        } // namespace cellular
    }     // namespace map
} // namespace bomberman