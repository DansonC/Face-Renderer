//output.hpp

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

//-------------------//
//---   Headers   ---//
//-------------------//
// Renderer Headers
#include "../include/renderer.hpp"
#include "../include/event_handler.hpp"
#include "../include/save_png.hpp"

// System Headers
#include <chrono>
#include <vector>


//---------------------//
//---   Functions   ---//
//---------------------//
void output(GLFWwindow *mWindow, GLuint shaderProgram, vector<parameters> &views);

#endif