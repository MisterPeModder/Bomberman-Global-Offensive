/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Users
*/

#include "Users.hpp"
#include "logger/Logger.hpp"

namespace game
{
    Users::Users()
    {
        for (size_t i = 0; i < static_cast<size_t>(User::UserId::UserCount); i++) {
            _users[i].setId(static_cast<User::UserId>(i));
            if (i == 0)
                _users[i].setSkin(User::USER_SKINS::TERRORIST_1);
            else
                _users[i].setSkin(User::USER_SKINS::UNKNOWN);
        }
        _users[0].setAvailable();
    }

    const User &Users::operator[](User::UserId id) const { return _users[static_cast<size_t>(id)]; }

    User &Users::operator[](User::UserId id) { return _users[static_cast<size_t>(id)]; }

    Users::ActionEvent Users::getNextAction()
    {
        for (size_t i = 0; i < static_cast<size_t>(User::UserId::UserCount); i++) {
            if (!_users[i].isAvailable())
                continue;
            GameAction action = _users[i].getChangedAction();

            if (action != GameAction::NONE)
                return ActionEvent{static_cast<User::UserId>(i), action, _users[i].getActionValue(action)};
        }
        return {User::UserId::UserCount, GameAction::NONE, 0};
    }

    void Users::setIgnoreKeyboard(bool ignore) noexcept
    {
        for (size_t i = 0; i < static_cast<size_t>(User::UserId::UserCount); ++i)
            this->_users[i].setIgnoreKeyboard(ignore);
    }

    bool Users::isGamepadUsed(int gamepadId) const
    {
        auto gamepad = raylib::core::Gamepad(gamepadId);

        if (!gamepad.isAvailable())
            return false;
        for (size_t i = 0; i < static_cast<size_t>(User::UserId::UserCount); i++)
            if (_users[i].isAvailable() && _users[i].getGamepadId() == gamepadId)
                return true;
        return false;
    }

    int Users::getJoiningGamepad() const
    {
        raylib::core::Gamepad::Button btn = raylib::core::Gamepad::getButtonPressed();

        if (static_cast<int>(btn) == -1)
            return -1;
        for (int id = 0; id < 4; id++) {
            auto gamepad = raylib::core::Gamepad(id);

            if (gamepad.isAvailable() && !isGamepadUsed(id) && gamepad.isButtonDown(btn))
                return id;
        }
        return -1;
    }

    unsigned int Users::getAvailableUsers() const
    {
        unsigned int count = 0;

        for (size_t i = 0; i < 4; i++)
            count += _users[i].isAvailable();
        return count;
    }

    void Users::connectUser(int gamepadId, User::USER_SKINS skin)
    {
        unsigned int nbUsers = getAvailableUsers();

        if (nbUsers >= 4)
            return;
        _users[nbUsers].setAvailable();
        _users[nbUsers].setGamepadId(gamepadId);
        _users[nbUsers].setSkin(skin);
        _users[nbUsers].updateActions(false);
        Logger::logger.log(Logger::Severity::Information,
            [&](auto &out) { out << "User " << nbUsers + 1 << " connected with gamepad " << gamepadId; });
    }

    bool Users::disconnectUser(User::UserId user)
    {
        unsigned int nbUsers = getAvailableUsers();

        if (nbUsers == 1) {
            if (!_users[0].isKeyboard()) {
                _users[0].setKeyboard();
                Logger::logger.log(Logger::Severity::Information, "User 1 switched to keyboard mode.");
            }
            return false;
        }
        size_t userPos = static_cast<size_t>(user);

        Logger::logger.log(Logger::Severity::Information, [&](auto &out) {
            out << "User " << nbUsers - 1 << " with gamepad " << _users[userPos].getGamepadId() << " disconnected";
        });
        for (size_t i = userPos; i < nbUsers - 1; i++) {
            _users[i].setGamepadId(_users[i + 1].getGamepadId());
            _users[i].setSkin(_users[i + 1].getSkin());
        }
        _users[nbUsers - 1].setAvailable(false);
        _users[nbUsers - 1].setSkin(User::USER_SKINS::UNKNOWN);
        return true;
    }

    User::USER_SKINS Users::getUserSkin(unsigned int id) { return _users[id].getSkin(); }

    localization::ResourceString Users::userSkinToRessourceString(User::USER_SKINS skin)
    {
        switch (skin) {
            case User::USER_SKINS::TERRORIST_1: return localization::resources::textures::rsTerroristOne;
            case User::USER_SKINS::TERRORIST_2: return localization::resources::textures::rsTerroristTwo;
            case User::USER_SKINS::COUNTER_TERRORIST_1: return localization::resources::textures::rsCounterTerroristOne;
            case User::USER_SKINS::COUNTER_TERRORIST_2: return localization::resources::textures::rsCounterTerroristTwo;
            case User::USER_SKINS::NO_SENSE: return localization::resources::textures::rsNoSense;
            case User::USER_SKINS::RAINBOW: return localization::resources::textures::rsRainbow;
            default: return localization::resources::textures::rsUnknown;
        }
    }

    std::queue<std::string> Users::prepareSkinParameters()
    {
        std::queue<std::string> skinQueue;

        for (unsigned int i = 0; i < getAvailableUsers(); i++)
            skinQueue.push(std::string(userSkinToRessourceString(_users[i].getSkin()).getMsgId()));
        if (getAvailableUsers() == 1)
            skinQueue.push(std::string(userSkinToRessourceString(_users[0].getSkin()).getMsgId()));
        return skinQueue;
    }

    void Users::updateActions(bool fillChanged)
    {
        for (size_t i = 0; i < static_cast<size_t>(User::UserId::UserCount); i++)
            _users[i].updateActions(fillChanged);
    }

    void Users::save()
    {
        for (size_t i = 0; i < static_cast<size_t>(User::UserId::UserCount); i++)
            _users[i].getProfile().save();
    }

    void Users::loadDefaults()
    {
        for (size_t i = 0; i < static_cast<size_t>(User::UserId::UserCount); i++)
            _users[i].getProfile().loadDefaults();
    }

} // namespace game
