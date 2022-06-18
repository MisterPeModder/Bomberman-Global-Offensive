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
        Animation::Animation(const std::filesystem::path &animPath)
            : _animationPath(animPath), _animFrameCounter(0), _animNumber(0)
        {
            _animations = LoadModelAnimations(animPath.generic_string().c_str(), &_animsCount);
        }

        Animation::~Animation()
        {
            if (_animations)
                UnloadModelAnimations(_animations, _animsCount);
        }

        Animation::Animation(const Animation &other)
            : _animationPath(other._animationPath), _animFrameCounter(other._animFrameCounter)
        {
            _animations = LoadModelAnimations(_animationPath.generic_string().c_str(), &_animsCount);
        }

        Animation &Animation::operator=(const Animation &other)
        {
            _animFrameCounter = other._animFrameCounter;
            _animationPath = other._animationPath;
            _animations = LoadModelAnimations(_animationPath.generic_string().c_str(), &_animsCount);

            return *this;
        }

        void Animation::chooseAnimation(unsigned int animationId)
        {
            if (animationId > _animsCount)
                throw std::logic_error("Try to use a non-existent animation.");
            _animNumber = animationId;
            _animFrameCounter = 0;
        }

        void Animation::updateModel(Model &model)
        {
            if (!_animations)
                return;
            _animFrameCounter++;
            UpdateModelAnimation(model.asRaylib(), _animations[_animNumber], _animFrameCounter);
            if (_animFrameCounter >= _animations[_animNumber].frameCount)
                _animFrameCounter = 0;
        }
    } // namespace model
} // namespace raylib
