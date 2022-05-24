/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Map
*/

#ifndef GAME_MAP_HPP_
#define GAME_MAP_HPP_

#include <ostream>
#include <vector>

namespace bomberman
{
    namespace map
    {
        class Map {
          public:
            enum class Element {
                Wall,
                Crate,
                Empty,

            };

            Map(size_t width = 13, size_t height = 13);
            ~Map() = default;

            void generate(size_t width, size_t height);
            void debugDisplay(std::ostream &stream) const;

            Element getElement(size_t x, size_t y) const;
            Element &getElement(size_t x, size_t y);

            size_t getWidth() const;
            size_t getHeight() const;

          private:
            size_t _width;
            size_t _height;

            std::vector<Element> _map;
        };
    } // namespace map
} // namespace bomberman

std::ostream &operator<<(std::ostream &stream, const bomberman::map::Map &map);

#endif /* !GAME_MAP_HPP_ */
