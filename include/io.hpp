// io.hpp

#ifndef IO_HPP
#define IO_HPP

#include <glad/glad.h>
//#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void input(string filename, GLfloat *data);
void input(string filename, GLuint *data);

#endif