/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Map
*/

#include "Map.hpp"
#include <iostream>
#include <stdexcept>

namespace bomberman
{
    namespace map
    {
        Map::Map(size_t width, size_t height) { generate(width, height); }

        void Map::generate(size_t width, size_t height)
        {
            if (width % 2 == 0 || height % 2 == 0)
                throw std::logic_error("Map must be odd."); /// Replace with custom exception
            _width = width;
            _height = height;

            _map.resize(_width * _height);
            std::fill(_map.begin(), _map.end(), Element::Empty);
            for (size_t x = 0; x < _width; x++) {
                for (size_t y = 0; y < _height; y++) {
                    if (x % 2 && y % 2)
                        getElement(x, y) = Element::Wall;
                }
            }
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
