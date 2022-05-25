/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Animation
*/

#include "Animation.hpp"

namespace raylib
{
    namespace model
    {
        Animation::Animation(const std::filesystem::path &animPath) : _animationPath(animPath), _animFrameCounter(0)
        {
            _animations = LoadModelAnimations(animPath.c_str(), &_animsCount);
        }

        Animation::~Animation() { UnloadModelAnimations(_animations, _animsCount); }

        Animation::Animation(const Animation &other)
            : _animationPath(other._animationPath), _animFrameCounter(other._animFrameCounter)
        {
            _animations = LoadModelAnimations(_animationPath.c_str(), &_animsCount);
        }

        Animation &Animation::operator=(const Animation &other)
        {
            _animFrameCounter = other._animFrameCounter;
            _animationPath = other._animationPath;
            _animations = LoadModelAnimations(_animationPath.c_str(), &_animsCount);

            return *this;
        }

        void Animation::updateModel(Model &model)
        {
            _animFrameCounter++;
            UpdateModelAnimation(model.asRaylib(), _animations[0], _animFrameCounter);
            if (_animFrameCounter >= _animations[0].frameCount)
                _animFrameCounter = 0;
        }
    } // namespace model
} // namespace raylib
