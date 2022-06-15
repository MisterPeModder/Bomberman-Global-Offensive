/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Map
*/

#ifndef GAME_RESOURCES_RANDOM_DEVICE_HPP_
#define GAME_RESOURCES_RANDOM_DEVICE_HPP_

#include <random>
#include "ecs/resource/Resource.hpp"

namespace game::resources
{
    /// Game map resource.
    struct RandomDevice : public ecs::Resource {
      public:
        /// Construct a new Random Device resource
        RandomDevice() : _generation(_device()) {}

        /// Generate a random number in the interval [min, max]
        ///
        /// @tparam numeric type of the numbers.
        /// @param min minimum value.
        /// @param max maximum value.
        /// @return numeric value in the interval [min, max]
        template <typename numeric> numeric randInt(numeric min, numeric max)
        {
            std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

            return dist(_generation);
        }

      private:
        std::random_device _device;
        std::mt19937 _generation;
    };
} // namespace game::resources

#endif /* !GAME_RESOURCES_RANDOM_DEVICE_HPP_ */
