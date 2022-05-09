/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Camera3D
*/

#pragma once

#include "Vector3.hpp"
extern "C" {
    #include "raylib.h"
}

namespace raylib {

class Camera3D {
    public:
        Camera3D();
        ~Camera3D();
        void begin3D();
        void end3D();
        raylib::Vector3 getPosition() const;
        void setPosition(raylib::Vector3);
        raylib::Vector3 getTarget() const;
        void setTarget(raylib::Vector3);
        raylib::Vector3 getUp() const;
        void setUp(raylib::Vector3);
        float getFovy() const;
        void setFovy(float);
        int getProjection() const;
        void setProjection(int);

    protected:
    private:
        ::Camera3D _camera;
};

}
