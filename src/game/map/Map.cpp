/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Map
*/

#include "Map.hpp"
#include <algorithm>
#include <random>
#include "cellular/Grid.hpp"

namespace game
{
    namespace map
    {
        Map::InvalidMapSize::InvalidMapSize(std::string_view message) : std::logic_error(message.data()) {}

        Map::Map(Vector2u size) { generate(size); }

        void Map::generate(Vector2u size)
        {
            if (size.x % 2 == 0 || size.y % 2 == 0)
                throw InvalidMapSize("Map width and height must be odd.");
            if (size.x < 3 || size.y < 3)
                throw InvalidMapSize("Map cannot be smaller than 3x3.");
            _size = size;
            _map.resize(size.x * size.y);

            cellular::Grid automata(size.x, size.y);
            automata.generate(cellular::Rule("B3/S012345678"), 15, 60);

            std::fill(_map.begin(), _map.end(), Element::Empty);
            for (unsigned int x = 0; x < _size.x; x++) {
                for (unsigned int y = 0; y < _size.y; y++) {
                    if (x % 2 && y % 2)
                        getElement({x, y}) = Element::Wall;
                    else if (automata.isFilled(x, y))
                        getElement({x, y}) = Element::Crate;
                }
            }
            freeCorners();
        }

        Map::Element Map::getElement(Vector2u size) const
        {
            if (size.x >= _size.x || size.y >= _size.y)
                throw std::out_of_range("Accessing out of bounds map element.");
            return _map[size.y * _size.x + size.x];
        }

        Map::Element &Map::getElement(Vector2u size)
        {
            if (size.x >= _size.x || size.y >= _size.y)
                throw std::out_of_range("Accessing out of bounds map element.");
            return _map[size.y * _size.x + size.x];
        }

        raylib::core::Vector2u Map::getSize() const { return _size; }

        Vector2 Map::getPlayerStartingPosition(game::User::UserId playerId)
        {
            return {static_cast<float>((static_cast<size_t>(playerId) % 2) * (_size.x - 1)),
                static_cast<float>((static_cast<size_t>(playerId) / 2) * (_size.y - 1))};
        }

        void Map::fillExplodedPositions(std::vector<Vector2u> &explodePositions, Vector2u center, size_t radius)
        {
            center = {std::clamp(center.x, 0u, _size.x - 1), std::clamp(center.y, 0u, _size.y - 1)};
            std::array<bool, 4> blocked;
            Vector2u current;
            int validWays = 4;

            blocked.fill(false);
            explodePositions.push_back(center);
            for (unsigned int i = 1; i < radius + 1 && validWays > 0; i++) {
                for (size_t j = 0; j < 4; j++) {
                    if (blocked[j])
                        continue;
                    bool valid = false;

                    switch (j) {
                        case 0:
                            current = {center.x - i, center.y};
                            valid = current.x < _size.x;
                            break;
                        case 1:
                            current = {center.x + i, center.y};
                            valid = current.x < _size.x;
                            break;
                        case 2:
                            current = {center.x, center.y - i};
                            valid = current.y < _size.y;
                            break;
                        case 3:
                            current = {center.x, center.y + i};
                            valid = current.y < _size.y;
                            break;
                        default: break;
                    }
                    /// Out of bounds or indestructible wall
                    if (!valid || getElement(current) == Element::Wall) {
                        blocked[j] = true;
                        validWays--;
                    } else
                        explodePositions.push_back(current);
                }
            }
        }

        void Map::freeCorners()
        {
            for (unsigned int y = 0; y < _size.y; y += _size.y - 1) {
                for (unsigned int x = 0; x < _size.x; x += _size.x - 1) {
                    getElement({x, y}) = Element::Empty;
                    getElement({x + ((x == 0) ? 1 : -1), y}) = Element::Empty;
                    getElement({x + ((x == 0) ? 2 : -2), y}) = Element::Crate;
                    getElement({x, y + ((y == 0) ? 1 : -1)}) = Element::Empty;
                    getElement({x, y + ((y == 0) ? 2 : -2)}) = Element::Crate;
                }
            }
        }
    } // namespace map
} // namespace game

std::ostream &operator<<(std::ostream &stream, const game::map::Map &map)
{
    for (size_t x = 0; x < map.getSize().x + 1; x++)
        stream << '_';
    stream << '\n';
    for (unsigned int y = 0; y < map.getSize().y; y++) {
        stream << '|';
        for (unsigned int x = 0; x < map.getSize().x; x++) {
            switch (map.getElement({x, y})) {
                case game::map::Map::Element::Wall: stream << 'X'; break;
                case game::map::Map::Element::Crate: stream << 'c'; break;
                case game::map::Map::Element::Empty: stream << ' '; break;
                default: break;
            }
        }
        stream << "|\n";
    }
    for (size_t x = 0; x < map.getSize().x + 1; x++)
        stream << '_';
    return stream << '\n';
}
