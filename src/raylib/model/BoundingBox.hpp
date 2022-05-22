/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** BoundingBox
*/

#ifndef RAYLIB_MODEL_BOUNDINGBOX_HPP_
#define RAYLIB_MODEL_BOUNDINGBOX_HPP_

#include "Model.hpp"

namespace raylib
{
    namespace model
    {
        class BoundingBox {
          public:
            // static inline getFromModel(const Model model)
            // {
            //   return GetModelBoundingBox(model.toRaylib());
            // }
            static inline ::BoundingBox getFromModel(const ::Model model)
            {
              return GetModelBoundingBox(model);
            }

          protected:
          private:
        };
    }
}

#endif /* !RAYLIB_MODEL_BOUNDINGBOX_HPP_ */
