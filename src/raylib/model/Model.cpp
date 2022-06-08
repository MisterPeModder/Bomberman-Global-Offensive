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
        Model::Model(const std::filesystem::path &modelPath) : _model(LoadModel(modelPath.generic_string().c_str())) {}

        Model::Model(const raylib::model::Mesh &mesh) : _model(LoadModelFromMesh(mesh.asRaylib())) {}

        Model::~Model() { UnloadModel(_model); }

        void Model::draw(raylib::core::Vector3 position, float scale, raylib::core::Color tint) const
        {
            DrawModel(_model, position.asRaylib(), scale, tint.asRaylib());
        }

        void Model::draw(raylib::core::Vector3 position, raylib::core::Vector3 rotationAxis, float rotationAngle,
            raylib::core::Vector3 scale, raylib::core::Color tint) const
        {
            DrawModelEx(
                _model, position.asRaylib(), rotationAxis.asRaylib(), rotationAngle, scale.asRaylib(), tint.asRaylib());
        }

        void Model::drawWires(raylib::core::Vector3 position, float scale, raylib::core::Color tint) const
        {
            DrawModelWires(_model, position.asRaylib(), scale, tint.asRaylib());
        }

        void Model::drawWires(raylib::core::Vector3 position, raylib::core::Vector3 rotationAxis, float rotationAngle,
            raylib::core::Vector3 scale, raylib::core::Color tint) const
        {
            DrawModelWiresEx(
                _model, position.asRaylib(), rotationAxis.asRaylib(), rotationAngle, scale.asRaylib(), tint.asRaylib());
        }

        BoundingBox Model::getBoundingBox() const { return BoundingBox(*this); }

        bool Model::checkCollision(const Model &other)
        {
            return getBoundingBox().checkCollision(other.getBoundingBox());
        }

        bool Model::checkCollision(const BoundingBox &otherBox) { return getBoundingBox().checkCollision(otherBox); }

        ::Model &Model::asRaylib() { return _model; }

        ::Model const &Model::asRaylib() const { return _model; }

        void Model::setMaterialMapTexture(const raylib::textures::Texture2D &texture, int materialId, int mapId)
        {
            _model.materials[materialId].maps[mapId].texture = texture.asRaylib();
        }

    } // namespace model
} // namespace raylib
