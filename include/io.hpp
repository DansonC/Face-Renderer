// io.hpp

#ifndef IO_HPP
#define IO_HPP

//-------------------//
//---   Headers   ---//
//-------------------//
// Renderer Headers
#include "../include/FaceRenderer3D.hpp"
#include "../include/event_handler.hpp"

// System Headers
#include <glad/glad.h>

// Standard Headers
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


//---------------------//
//---   Functions   ---//
//---------------------//
void input(string filename, GLfloat *data);
void input(string filename, GLuint *data);
void input(string filename, vector<parameters> &data);

#endif
