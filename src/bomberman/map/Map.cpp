/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Map
*/

#include "Map.hpp"
#include <iostream>
#include <random>
#include <stdexcept>
#include "cellular/Grid.hpp"

namespace bomberman
{
    namespace map
    {
        Map::Map(size_t fillPercent, size_t width, size_t height) { generate(fillPercent, width, height); }

        void Map::generate(size_t fillPercent, size_t width, size_t height)
        {
            if (width % 2 == 0 || height % 2 == 0)
                throw std::logic_error("Map must be odd."); /// Replace with custom exception
            if (width < 3 || height < 3)
                throw std::logic_error("Map cannot be smaller than 3x3."); /// Replace with custom exception
            _width = width;
            _height = height;
            _map.resize(_width * _height);

            cellular::Grid automata(width, height);
            automata.generate(cellular::Rule("B1357/S1357"), 5, fillPercent);

            std::fill(_map.begin(), _map.end(), Element::Empty);
            for (size_t x = 0; x < _width; x++) {
                for (size_t y = 0; y < _height; y++) {
                    if (x % 2 && y % 2)
                        getElement(x, y) = Element::Wall;
                    else if (automata.at(x, y))
                        getElement(x, y) = Element::Crate;
                }
            }
            freeCorners();
        }

        Map::Element Map::getElement(size_t x, size_t y) const
        {
            if (x >= _width || y >= _height)
                throw std::out_of_range("Accessing out of bounds map element."); /// Replace with custom exception
            return _map[y * _width + x];
        }

        Map::Element &Map::getElement(size_t x, size_t y)
        {
            if (x >= _width || y >= _height)
                throw std::out_of_range("Accessing out of bounds map element."); /// Replace with custom exception
            return _map[y * _width + x];
        }

        size_t Map::getWidth() const { return _width; }

        size_t Map::getHeight() const { return _height; }

        void Map::freeCorners()
        {
            for (size_t y = 0; y < _height; y += _height - 1) {
                for (size_t x = 0; x < _width; x += _width - 1) {
                    getElement(x, y) = Element::Empty;
                    getElement(x + ((x == 0) ? 1 : -1), y) = Element::Empty;
                    getElement(x, y + ((y == 0) ? 1 : -1)) = Element::Empty;
                }
            }
        }
    } // namespace map
} // namespace bomberman

std::ostream &operator<<(std::ostream &stream, const bomberman::map::Map &map)
{
    for (size_t x = 0; x < map.getWidth() + 1; x++)
        stream << '_';
    stream << '\n';
    for (size_t y = 0; y < map.getHeight(); y++) {
        stream << '|';
        for (size_t x = 0; x < map.getWidth(); x++) {
            switch (map.getElement(x, y)) {
                case bomberman::map::Map::Element::Wall: stream << 'X'; break;
                case bomberman::map::Map::Element::Crate: stream << 'c'; break;
                case bomberman::map::Map::Element::Empty: stream << ' '; break;
                default: break;
            }
        }
        stream << "|\n";
    }
    for (size_t x = 0; x < map.getWidth() + 1; x++)
        stream << '_';
    return stream << '\n';
}
