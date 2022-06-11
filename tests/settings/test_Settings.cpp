/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** test_settings
*/

#include "game/settings/Settings.hpp"

#include <gtest/gtest.h>

using namespace game::settings;

TEST(Settings, sfx)
{
    Settings settings;

    EXPECT_EQ(settings.getSfxVolume(), 100);
    EXPECT_THROW(settings.setSfxVolume(-1), Settings::InvalidSettingsValue);
    EXPECT_THROW(settings.setSfxVolume(101), Settings::InvalidSettingsValue);
    EXPECT_EQ(settings.getSfxVolume(), 100);
    settings.setSfxVolume(30);
    EXPECT_EQ(settings.getSfxVolume(), 30);
    settings.loadDefaults();
    EXPECT_EQ(settings.getSfxVolume(), 100);
}

TEST(Settings, music)
{
    Settings settings;

    EXPECT_EQ(settings.getMusicVolume(), 100);
    EXPECT_THROW(settings.setMusicVolume(-1), Settings::InvalidSettingsValue);
    EXPECT_THROW(settings.setMusicVolume(101), Settings::InvalidSettingsValue);
    EXPECT_EQ(settings.getMusicVolume(), 100);
    settings.setMusicVolume(30);
    EXPECT_EQ(settings.getMusicVolume(), 30);
    settings.loadDefaults();
    EXPECT_EQ(settings.getMusicVolume(), 100);
}

TEST(Settings, load)
{
    Settings settings;

    /// Default values
    EXPECT_EQ(settings.getMusicVolume(), 100);
    EXPECT_EQ(settings.getSfxVolume(), 100);
    EXPECT_EQ(settings.getTargetFramerate(), 60);
    EXPECT_EQ(settings.getResolution(), raylib::core::Vector2f(1280, 720));
    EXPECT_FALSE(settings.isFullscreen());
    /// Loaded values (music and target framerate are invalid and therefore set to default)
    settings.load();
    EXPECT_EQ(settings.getMusicVolume(), 100);
    EXPECT_EQ(settings.getSfxVolume(), 10);
    EXPECT_EQ(settings.getTargetFramerate(), 60);
    EXPECT_EQ(settings.getResolution(), raylib::core::Vector2f(1920, 1080));
    EXPECT_TRUE(settings.isFullscreen());
}
