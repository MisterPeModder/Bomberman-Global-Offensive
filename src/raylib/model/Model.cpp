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
        Model::Model(const std::filesystem::path &modelPath)
            : _model(LoadModel(modelPath.generic_string().c_str())), _path(modelPath)
        {
        }

        Model::Model(const raylib::model::Mesh &mesh) : _model(loadFromMesh(mesh)) {}///

        Model::Model(const ::Mesh &mesh) { _model = LoadModelFromMesh(mesh); }

        Model::Model(const raylib::model::Mesh &mesh, const raylib::textures::Texture2D &texture, int materialId, int mapType) : Model(mesh)
        {
            setMaterialMapTexture(texture, materialId, mapType);
        }

        Model::~Model() { UnloadModel(_model); }

        void Model::draw(raylib::core::Vector3f position, float scale, raylib::core::Color tint) const
        {
            DrawModel(_model, position.asRaylib(), scale, tint.asRaylib());
        }

        void Model::draw(raylib::core::Vector3f position, raylib::core::Vector3f rotationAxis, float rotationAngle,
            raylib::core::Vector3f scale, raylib::core::Color tint) const
        {
            DrawModelEx(
                _model, position.asRaylib(), rotationAxis.asRaylib(), rotationAngle, scale.asRaylib(), tint.asRaylib());
        }

        void Model::drawWires(raylib::core::Vector3f position, float scale, raylib::core::Color tint) const
        {
            DrawModelWires(_model, position.asRaylib(), scale, tint.asRaylib());
        }

        void Model::drawWires(raylib::core::Vector3f position, raylib::core::Vector3f rotationAxis, float rotationAngle,
            raylib::core::Vector3f scale, raylib::core::Color tint) const
        {
            DrawModelWiresEx(
                _model, position.asRaylib(), rotationAxis.asRaylib(), rotationAngle, scale.asRaylib(), tint.asRaylib());
        }

        BoundingBox Model::getBoundingBox() const { return BoundingBox(*this); }

        bool Model::checkCollision(const Model &other)
        {
            return getBoundingBox().checkCollision(other.getBoundingBox());
        }

        ::Model Model::loadFromMesh(const ::Mesh &mesh) { return LoadModelFromMesh(mesh); }

        ::Model Model::loadFromMesh(const raylib::model::Mesh &mesh) { return LoadModelFromMesh(mesh.asRaylib()); }

        bool Model::checkCollision(const BoundingBox &otherBox) { return getBoundingBox().checkCollision(otherBox); }

        ::Model &Model::asRaylib() { return _model; }

        ::Model const &Model::asRaylib() const { return _model; }

        Model::Model(const Model &other) : _path(other._path) { _model = LoadModel(_path.generic_string().c_str()); }

        void Model::setMaterialMapTexture(const raylib::textures::Texture2D &texture, int materialId, int mapType)
        {
            SetMaterialTexture(&_model.materials[materialId], mapType, texture.asRaylib());
        }

    } // namespace model
} // namespace raylib
