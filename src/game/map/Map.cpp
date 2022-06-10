/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Map
*/

#include "Map.hpp"
#include <iostream>
#include <random>
#include "cellular/Grid.hpp"

namespace game
{
    namespace map
    {
        Map::InvalidMapSize::InvalidMapSize(std::string_view message) : std::logic_error(message.data()) {}

        Map::Map(size_t width, size_t height) { generate(width, height); }

        void Map::generate(size_t width, size_t height)
        {
            if (width % 2 == 0 || height % 2 == 0)
                throw InvalidMapSize("Map width and height must be odd.");
            if (width < 3 || height < 3)
                throw InvalidMapSize("Map cannot be smaller than 3x3.");
            _width = width;
            _height = height;
            _map.resize(_width * _height);

            cellular::Grid automata(width, height);
            automata.generate(cellular::Rule("B3/S012345678"), 15, 60);

            std::fill(_map.begin(), _map.end(), Element::Empty);
            for (size_t x = 0; x < _width; x++) {
                for (size_t y = 0; y < _height; y++) {
                    if (x % 2 && y % 2)
                        getElement(x, y) = Element::Wall;
                    else if (automata.isFilled(x, y))
                        getElement(x, y) = Element::Crate;
                }
            }
            freeCorners();
        }

        Map::Element Map::getElement(size_t x, size_t y) const
        {
            if (x >= _width || y >= _height)
                throw std::out_of_range("Accessing out of bounds map element.");
            return _map[y * _width + x];
        }

        Map::Element &Map::getElement(size_t x, size_t y)
        {
            if (x >= _width || y >= _height)
                throw std::out_of_range("Accessing out of bounds map element.");
            return _map[y * _width + x];
        }

        size_t Map::getWidth() const { return _width; }

        size_t Map::getHeight() const { return _height; }

        Vector2 Map::getPlayerStartingPosition(game::User::UserId playerId)
        {
            return {static_cast<float>((static_cast<size_t>(playerId) % 2) * (getWidth() - 1)),
                static_cast<float>((static_cast<size_t>(playerId) / 2) * (getHeight() - 1))};
        }

        void Map::freeCorners()
        {
            for (size_t y = 0; y < _height; y += _height - 1) {
                for (size_t x = 0; x < _width; x += _width - 1) {
                    getElement(x, y) = Element::Empty;
                    getElement(x + ((x == 0) ? 1 : -1), y) = Element::Empty;
                    getElement(x + ((x == 0) ? 2 : -2), y) = Element::Crate;
                    getElement(x, y + ((y == 0) ? 1 : -1)) = Element::Empty;
                    getElement(x, y + ((y == 0) ? 2 : -2)) = Element::Crate;
                }
            }
        }
    } // namespace map
} // namespace game

std::ostream &operator<<(std::ostream &stream, const game::map::Map &map)
{
    for (size_t x = 0; x < map.getWidth() + 1; x++)
        stream << '_';
    stream << '\n';
    for (size_t y = 0; y < map.getHeight(); y++) {
        stream << '|';
        for (size_t x = 0; x < map.getWidth(); x++) {
            switch (map.getElement(x, y)) {
                case game::map::Map::Element::Wall: stream << 'X'; break;
                case game::map::Map::Element::Crate: stream << 'c'; break;
                case game::map::Map::Element::Empty: stream << ' '; break;
                default: break;
            }
        }
        stream << "|\n";
    }
    for (size_t x = 0; x < map.getWidth() + 1; x++)
        stream << '_';
    return stream << '\n';
}
