//renderer.hpp

#ifndef RENDERER_HPP
#define RENDERER_HPP

//-------------------//
//---   Headers   ---//
//-------------------//
// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <vector>

// Standard Headers
//#include <cstdio>
//#include <cstdlib>
//#include <cstring>
#include <unistd.h>

// Renderer Headers
#include "../include/event_handler.hpp"
#include "../include/save_png.hpp"

//---------------------//
//---   Constants   ---//
//---------------------//
const int windowWidth = 400;
const int windowHeight = 400;

//---------------------//
//---   Functions   ---//
//---------------------//
void output(GLFWwindow *mWindow, GLuint shaderProgram, vector<parameters> &views);
void ui(GLFWwindow *mWindow, GLuint shaderProgram, parameters &params);

#endif
