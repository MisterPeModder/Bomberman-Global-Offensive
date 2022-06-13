/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** CreateMap
*/

#include "CreateMap.hpp"

void createMap(ecs::World &world,  game::map::Map &map)
{
    raylib::textures::Texture2D texture("src/crate.png");
    raylib::model::Mesh mesh = mesh.genCube({1.0f, 1.0f, 1.0f});
    raylib::model::Model model(mesh);

    raylib::textures::Texture2D texture_ground("src/minecraft.png");
    raylib::model::Mesh mesh_ground = mesh_ground.genCube({map.getHeight() + 1.f, 0.0f, map.getWidth() + 1.f});
    raylib::model::Model model_ground(mesh_ground);

    raylib::textures::Texture2D texture_wall("src/wall.png");
    raylib::model::Mesh mesh_wall = mesh_wall.genCube({1.0f, 1.0f, 1.0f});
    raylib::model::Model model_wall(mesh_wall);

    model_ground.setMaterialMapTexture(texture_ground, 0, MATERIAL_MAP_DIFFUSE);
    model_wall.setMaterialMapTexture(texture_wall, 0, MATERIAL_MAP_DIFFUSE);
    model.setMaterialMapTexture(texture, 0, MATERIAL_MAP_DIFFUSE);

    // camera.setPosition({20.0f, 20.0f, map.getWidth() / 2.f});
    // camera.setTarget({map.getWidth() / 2.fcrate
    // camera.setProjection(CAMERA_PERSPECTIVE);
    // camera.setMode(raylib::core::Camera3D::CameraMode::ORBITAL);

    world.addResource<ecs::Timer>();
    world.addSystem<game::systems::DrawModel>();

    // create ground
     world.addEntity()
        .with<game::Position>(0 + (map.getWidth() / 2.f), -0.5f, 0 + (map.getHeight() / 2.f))
        .with<game::Scale>(1.f)
        .with<game::Color>(raylib::core::Color::WHITE) // raylib::core::Color(0, 228, 48, 255))
        .with<game::Model>(model_ground)
        .build();

    // create border
    for (int y = -1; y <= ((int)map.getHeight()); y++) {
        for (int x = -1; x <= ((int)map.getWidth()); x++) {
            if (x == -1 || x == ((int)map.getWidth()) || y == -1 || y == ((int)map.getHeight()))
                world.addEntity()
                    .with<game::Position>(static_cast<float>(x), 0.f, static_cast<float>(y))
                    .with<game::Scale>(1.f)
                    .with<game::Color>(raylib::core::Color::WHITE) // 0, 0, 250, 255)
                    .with<game::Model>(model_wall)
                    .build();
        }
    }

    // create map
    for (int y = 0; y != (int)map.getHeight(); y++) {
        for (int x = 0; x != (int)map.getWidth(); x++) {
            if (map.getElement(x, y) == game::map::Map::Element::Crate) {
                world.addEntity()
                    .with<game::Position>(static_cast<float>(x), 0.f, static_cast<float>(y))
                    .with<game::Scale>(1.f)
                    .with<game::Color>(raylib::core::Color::WHITE) // 250, 0, 0, 255)
                    .with<game::Model>(model)
                    .build();
            }
            if (map.getElement(x, y) == game::map::Map::Element::Wall) {
                world.addEntity()
                    .with<game::Position>(static_cast<float>(x), 0.f, static_cast<float>(y))
                    .with<game::Scale>(1.f)
                    .with<game::Color>(raylib::core::Color::WHITE) // 0, 0, 250, 255)
                    .with<game::Model>(model_wall)
                    .build();
            }
        }
    }
}
