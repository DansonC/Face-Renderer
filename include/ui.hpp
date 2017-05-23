//ui.hpp

#ifndef UI_HPP
#define UI_HPP

//-------------------//
//---   Headers   ---//
//-------------------//
// Renderer Headers
#include "../include/renderer.hpp"
#include "../include/event_handler.hpp"
#include "../include/save_png.hpp"

// System Headers
#include <chrono>


//---------------------//
//---   Functions   ---//
//---------------------//
void ui(GLFWwindow *mWindow, GLuint shaderProgram, parameters &params);

#endif