/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** AI Updating
*/

#include "AiUpdate.hpp"

#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Entities.hpp"

#include "game/components/AiControlable.hpp"
#include "game/components/Player.hpp"
#include "game/components/Position.hpp"

#include <algorithm>
#include <cmath>
#include <optional>
#include <utility>
#include "logger/Logger.hpp"

using raylib::core::Vector2f;
using raylib::core::Vector3f;

namespace game::systems
{
    static std::optional<std::pair<Vector2f, Vector2f>> nextGoal(Vector3f &pos, game::components::AiControlable &ai)
    {
        if (ai.path.empty())
            return {};
        Vector2f goal(ai.path[0]);
        Vector2f dist(std::fabs(pos.x - goal.x), std::fabs(pos.z - goal.y));

        // Pop the goal node if reached
        while (dist.x < 0.2 && dist.y < 0.2) {
            ai.path.pop_front();
            pos.x = goal.x;
            pos.z = goal.y;
            if (ai.path.empty())
                return {};
            goal = ai.path[0];
            dist = {std::fabs(pos.x - goal.x), std::fabs(pos.z - goal.y)};
        }
        return std::optional(std::make_pair(goal, dist));
    }

    void AiUpdate::run(ecs::SystemData data)
    {
        auto &entities = data.getResource<ecs::Entities>();
        auto &positions = data.getStorage<game::components::Position>();
        auto &ais = data.getStorage<game::components::AiControlable>();

        for (auto [self, pos, ai] : ecs::join(entities, positions, ais)) {
            auto next = nextGoal(pos, ai);

            if (!next) {
                game::components::Player::move(self, data, game::GameAction::MOVE_RIGHT, 0.0);
                continue;
            }
            Logger::logger.log(
                Logger::Severity::Debug, [&](auto &out) { out << "path size at update: " << ai.path.size(); });
            auto [goal, dist] = *next;

            if (dist.x > dist.y) {
                float value = std::min(dist.x, 1.f);
                if (pos.x < goal.x)
                    game::components::Player::move(self, data, game::GameAction::MOVE_RIGHT, value);
                else
                    game::components::Player::move(self, data, game::GameAction::MOVE_LEFT, value);
            } else {
                float value = std::min(dist.y, 1.f);
                if (pos.z < goal.y)
                    game::components::Player::move(self, data, game::GameAction::MOVE_DOWN, value);
                else
                    game::components::Player::move(self, data, game::GameAction::MOVE_UP, value);
            }
        }
    }

} // namespace game::systems
