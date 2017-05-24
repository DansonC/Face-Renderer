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
#include "../include/lodepng.h"
#include <string>

class FaceRenderer3D
{
    public:
    //---------------------//
    //---   Functions   ---//
    //---------------------//
    FaceRenderer3D(GLfloat* vert, GLfloat* col, GLuint* elem, int num_vert, int num_col, int num_elem);
    ~FaceRenderer3D();
    int init();
    void destroy();
    void output(vector<parameters> &views, string directory);
    void ui();
    void save_png(string filename);
    //unsigned char* load_png(char* filename, unsigned int* image_w, unsigned int* image_h);

    private:
    //---------------------//
    //---   Constants   ---//
    //---------------------//
    const int windowWidth = 400;
    const int windowHeight = 400;

    // Shader sources
    const GLchar* vertexSource = R"glsl(
        #version 150 core
        in vec3 position;
        in vec3 color;

        out vec3 Color;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 proj;
        void main()
        {
        Color = color;
            gl_Position = proj * view * model * vec4(-1 * position.x, position.y, position.z, 1.0);
        }
    )glsl";
    const GLchar* fragmentSource = R"glsl(
        #version 150 core
        
        in vec3 Color;
        out vec4 outColor;
        void main()
        {
            outColor = vec4(Color, 1.0);
        }
    )glsl";


    GLfloat* vertices;
    GLfloat* colors;
    GLuint* elements;
    int vertices_size;
    int colors_size;
    int elements_size;

    GLuint vao;
    GLuint vbo;
    GLuint color_buffer;
    GLuint ebo;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLFWwindow *mWindow; 
    parameters params;
};

#endif
