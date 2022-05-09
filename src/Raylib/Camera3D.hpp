/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Camera3D
*/

#pragma once

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
        Vector3 getPosition() const;
        void setPosition(Vector3);
        Vector3 getTarget() const;
        void setTarget(Vector3);
        Vector3 getUp() const;
        void setUp(Vector3);
        float getFovy() const;
        void setFovy(float);
        int getProjection() const;
        void setProjection(int);

    protected:
    private:
        ::Camera3D _camera;
};

}
