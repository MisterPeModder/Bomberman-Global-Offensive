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
        /// Bomberman Map
        class Map {
          public:
            /// Map element
            enum class Element {
                Wall,  /// Indestructible wall
                Crate, /// Destructible crate
                Empty, /// Nothing

            };

            /// Construct a new Map
            ///
            /// @param fillPercent initial map cell fill, may change due to cellular automata.
            /// @param width width of the map
            /// @param height height of the map
            Map(size_t fillPercent = 40, size_t width = 13, size_t height = 13);

            /// Destroy the map
            ~Map() = default;

            /// Generate the map.
            ///
            /// @param fillPercent initial map cell fill, may change due to cellular automata.
            /// @param width width of the map
            /// @param height height of the map
            void generate(size_t fillPercent, size_t width, size_t height);

            /// Get the Element at the position (x, y)
            ///
            /// @param x x position
            /// @param y y position
            /// @return Element element at the position (x, y)
            Element getElement(size_t x, size_t y) const;

            /// Get the Element at the position (x, y)
            ///
            /// @param x x position
            /// @param y y position
            /// @return Element& element at the position (x, y)
            Element &getElement(size_t x, size_t y);

            /// Get the Width of the map
            ///
            /// @return size_t width
            size_t getWidth() const;

            /// Get the height of the map
            ///
            /// @return size_t height
            size_t getHeight() const;

          private:
            /// Ensure the corners to be empty to avoid invalid player spawn
            void freeCorners();

            size_t _width;
            size_t _height;
            size_t _fillPercent;

            std::vector<Element> _map;
        };
    } // namespace map
} // namespace bomberman

std::ostream &operator<<(std::ostream &stream, const bomberman::map::Map &map);

#endif /* !GAME_MAP_HPP_ */
