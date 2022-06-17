/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Animation
*/

#ifndef RAYLIB_MODEL_ANIMATION_HPP_
#define RAYLIB_MODEL_ANIMATION_HPP_

extern "C"
{
#include <raylib.h>
}

#include <filesystem>
#include <string>
#include "Model.hpp"

namespace raylib
{
    namespace model
    {
        /// The Animation class
        class Animation {
          public:
            /// Animation constructor. Used to initialize an animation from a file
            /// File format accepted: obj and probably some other
            ///
            /// @param animPath the relative path to the animation to import
            Animation(const std::filesystem::path &animPath);

            /// Animation destructor
            ~Animation();

            /// Copy constructor
            Animation(const Animation &other);

            /// Copy operator
            Animation &operator=(const Animation &other);

            /// Choose the animation to play
            ///
            /// @param animationId The id of the animation
            void chooseAnimation(unsigned int animationId);

            /// Update a model with this animation
            ///
            /// @param model The model to update
            void updateModel(Model &model);

          private:
            std::filesystem::path _animationPath;
            ::ModelAnimation *_animations;
            unsigned int _animsCount;
            unsigned int _animFrameCounter;
            unsigned int _animNumber;
        };
    } // namespace model
} // namespace raylib

#endif /* !RAYLIB_MODEL_ANIMATION_HPP_ */
