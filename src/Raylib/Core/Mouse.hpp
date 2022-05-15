/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Mouse
*/

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include "Vector2.hpp"

extern "C" {
    #include "raylib.h"
}

namespace raylib {
    namespace Core {
        class Mouse {
            public:

                /// @brief Constructor of the Mouse
                Mouse();

                /// @brief Destructor of the Mouse
                ~Mouse();

                /// @brief A wrapper function for the raylib function IsMouseButtonPressed.
                ///
                ///@param button The button to check.
                ///
                ///@return A boolean value.
                bool isMouseButtonPressed(int button); 
                
                /// @brief @brief It returns a bool value.
                ///
                ///@param button The button to check.
                ///
                ///@return A boolean value.
                bool isMouseButtonDown(int button);                 
                
                /// @brief A wrapper for the raylib function of the same name.
                ///
                ///@param button The mouse button to check.
                ///
                ///@return A boolean value.
                bool isMouseButtonReleased(int button); 
                
                /// @brief It returns true if the mouse button is up.
                ///
                ///@param button The button to check.
                ///
                ///@return A boolean value.
                bool isMouseButtonUp(int button);
                
                /// @brief It returns the mouse's x position.
                ///
                ///@return The mouse's x position.
                int getMouseX(void);                                                   
                
                /// @brief It returns the mouse's y position.
                ///
                ///@return The mouse's y position.
                int getMouseY(void);                                                   
                
                /// @brief It returns the mouse position.
                ///
                ///@return A Vector2 object.
                Vector2 getMousePosition(void);                                  
                
                /// @brief It returns the mouse delta.
                ///
                ///@return A Vector2 object.
                Vector2 getMouseDelta(void);                                      
                
                /// @brief Sets the mouse position
                ///
                ///@param x The x position of the mouse
                ///@param y The y position of the mouse.
                void setMousePosition(int x, int y);                                 
                
                /// @brief Sets the mouse offset
                ///
                ///@param offsetX The X offset of the mouse.
                ///@param offsetY The Y offset of the mouse.
                void setMouseOffset(int offsetX, int offsetY);                          
                
                /// @brief Sets mouse scaling
                ///
                ///@param scaleX Horizontal mouse scaling factor
                ///@param scaleY Vertical scaling factor for mouse input
                void setMouseScale(float scaleX, float scaleY);               
                
                /// @brief It returns the mouse wheel movement Y.
                ///
                /// @return The mouse wheel movement.
                float getMouseWheelMove(void);       
                
                /// @brief Sets the mouse cursor icon
                /// @param cursor The cursor to set.
                void setMouseCursor(int cursor);

            protected:
            private:
        };
    }
}

#endif /* !MOUSE_HPP_ */
