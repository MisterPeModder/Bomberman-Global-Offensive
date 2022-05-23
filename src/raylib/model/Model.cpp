/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Model
*/

#include "Model.hpp"
#include "BoundingBox.hpp"

namespace raylib
{
    namespace model
    {
        Model::Model(const std::string &modelPath)
        : _model(LoadModel(modelPath.c_str()))
        {
        }

        Model::~Model()
        {
            UnloadModel(_model);
        }

        void Model::draw(raylib::core::Vector3 position, float scale, raylib::core::Color tint) const
        {
            DrawModel(_model, position.toRaylib(), scale, tint.toRaylib());
        }

        void Model::draw(raylib::core::Vector3 position, raylib::core::Vector3 rotationAxis, float rotationAngle, raylib::core::Vector3 scale, raylib::core::Color tint) const
        {
            DrawModelEx(_model, position.toRaylib(), rotationAxis.toRaylib(), rotationAngle, scale.toRaylib(), tint.toRaylib());
        }

        void Model::drawWires(raylib::core::Vector3 position, float scale, raylib::core::Color tint) const
        {
            DrawModelWires(_model, position.toRaylib(), scale, tint.toRaylib());
        }

        void Model::drawWires(raylib::core::Vector3 position, raylib::core::Vector3 rotationAxis, float rotationAngle, raylib::core::Vector3 scale, raylib::core::Color tint) const
        {
            DrawModelWiresEx(_model, position.toRaylib(), rotationAxis.toRaylib(), rotationAngle, scale.toRaylib(), tint.toRaylib());
        }

        BoundingBox Model::getBoundingBox() const
        {
            return BoundingBox(_model);
        }

        bool Model::checkCollision(const Model& other)
        {
            return getBoundingBox().checkCollision(other.getBoundingBox());
        }

        bool Model::checkCollision(const BoundingBox& otherBox)
        {
            return getBoundingBox().checkCollision(otherBox);
        }

        ::Model Model::toRaylib() const {
            return _model;
        }

    }
}
