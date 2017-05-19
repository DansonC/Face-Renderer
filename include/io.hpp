// io.hpp

#ifndef IO_HPP
#define IO_HPP

//-------------------//
//---   Headers   ---//
//-------------------//
// System Headers
#include <glad/glad.h>
// Standard Headers
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void input(string filename, GLfloat *data);
void input(string filename, GLuint *data);

#endif