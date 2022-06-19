/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Sound
*/

#include "Sound.hpp"
#include "ecs/Storage.hpp"
#include "ecs/resource/Entities.hpp"
#include "game/resources/AssetMap.hpp"

namespace game::components
{
    void Sound::playSound(ecs::SystemData data, std::string_view name)
    {
        data.getResource<ecs::Entities>()
            .builder()
            .with<components::SoundReference>(data.getStorage<components::SoundReference>(),
                data.getResource<game::resources::Sounds>().get(name.data()))
            .build();
    }
} // namespace game::components
