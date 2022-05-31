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
            /// Cellular automata 2D grid
            class Grid {
              public:
                /// Create a new @b unitilialized 2D grid
                ///
                /// @param width width of the grid
                /// @param height height of the grid
                Grid(size_t width = 1, size_t height = 1);

                /// Destroy the grid
                ~Grid() = default;

                /// Generate the grid.
                /// @note The grid starts randomly filled (following @c fillPercent) and make @c iterations iterations
                /// on the cells following the rule @c rule.
                /// @note It will call @ref setRule() with @c rule.
                ///
                /// @param rule Rule to apply to the cells for each iterations.
                /// @param iterations number of iterations to make.
                /// @param fillPercent percentage of filled cell at the beginning.
                ///
                void generate(const Rule &rule, size_t iterations = 5, size_t fillPercent = 60);

                /// Generate the grid.
                /// @note The grid starts randomly filled (following @c fillPercent) and make @c iterations iterations
                /// on the cells following the loaded rule with @ref setRule().
                ///
                /// @param iterations number of iterations to make.
                /// @param fillPercent percentage of filled cell at the beginning.
                ///
                void generate(size_t iterations = 5, size_t fillPercent = 60);

                /// Clear the grid (fill it with empty cells)
                void clear();

                /// Randomly fill @c fillPercent percent of the cells.
                ///
                /// @param fillPercent percentage of cells to fill.
                void randomFill(size_t fillPercent);

                /// Execute an iteration of the grid following the current rule set with @ref setRule()
                void iterate();

                /// Get the internal grid.
                /// @note The index of the position (x, y) is [x + y * width]
                ///
                /// @return const std::vector<bool>& internal grid, filled cells have the value true.
                ///
                const std::vector<bool> &getGrid() const;

                /// Set the Rule
                ///
                /// @param rule rule to set.
                void setRule(const Rule &rule);

                /// Get the rule
                ///
                /// @return Rule rule set.
                const Rule &getRule() const;

                /// Test if the cell at the position (x, y) is filled
                ///
                /// @param x x position of the cell.
                /// @param y y position of the cell.
                /// @return true If the cell is filled.
                /// @return false If the cell is empty.
                /// @throw std::out_of_bounds when the position is out of the grid bounds
                bool isFilled(size_t x, size_t y) const;

                /// Change the size of the grid
                /// @note Changing the size will require to regenerate the grid
                ///
                /// @param width new width
                /// @param height new height
                void setSize(size_t width, size_t height);

              private:
                /// Test if the cell at the position (x, y) is filled, if it is in the border return false instead of
                /// raising exception like @ref isFilled().
                ///
                /// @param x x position of the cell.
                /// @param y y position of the cell.
                /// @return true If the cell is filled.
                /// @return false If the cell is empty.
                bool borderIsFilled(int x, int y) const;

                /// Get the number of filled neighbours of the cell at the position (x, y)
                ///
                /// @param x x position of the cell.
                /// @param y y position of the cell.
                /// @return unsigned char number of filled neighbours (0-8)
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
