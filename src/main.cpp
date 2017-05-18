// main.cpp

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <math.h>

// Support Headers
#include "../include/io.hpp"

#define SCREEN_WIDTH 4
#define SCREEN_HEIGHT 4
#define PIXEL_SIZE 2
#define SCREEN_OFFSET 0

const int VERTICES_SIZE = (53215 + 1) * 3;
const int COLORS_SIZE = VERTICES_SIZE;
const int ELEMENTS_SIZE = 105840 * 3;

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
        gl_Position = view * vec4(position, 1.0);
    }
)glsl";
//gl_Position = proj * view * trans * vec4(position, 1.0);
const GLchar* fragmentSource = R"glsl(
    #version 150 core
    
    in vec3 Color;
    out vec4 outColor;
    void main()
    {
        outColor = vec4(Color, 1.0);
    }
)glsl";
/*
const GLchar* vertexSource =
    "#version 150 core\n"
    "in vec2 position;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(position, 0.0, 1.0);\n"
    "}\n";
const GLchar* fragmentSource =
    "#version 150 core\n"
    "out vec4 outColor;\n"
    "void main()\n"
    "{\n"
    "    outColor = vec4(0.5, 1.0, 1.0, 1.0);\n"
    "}\n";
    */
int main(int argc, char * argv[]) {

    auto t_start = std::chrono::high_resolution_clock::now();

    int windowWidth = 800; // mWidth for full window
    int windowHeight = 600; // mHeight for full window

    // Load GLFW and Create a Window
    if(glfwInit() == false)
    {
        fprintf(stderr, "Failed to initialize OPENGL\n");
        return EXIT_FAILURE;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(windowWidth, windowHeight, "Face Triangulation", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    if(!gladLoadGL()) {
        fprintf(stderr, "Failed to Load OpenGL");
    }
    
// Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLuint color_buffer;
    glGenBuffers(1, &color_buffer);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    /*
    GLfloat vertices[] = {
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    GLfloat colors[] = {
         0.0f,  1.0f, 0.0f,
         1.0f,  0.0f, 0.0f,
         0.0f,  0.0f, 1.0f,
    };

    GLuint elements[] = {
	    0, 1, 2
    };
    */

    GLfloat vertices[VERTICES_SIZE];
    GLfloat colors[COLORS_SIZE];
    GLuint elements[ELEMENTS_SIZE];
    input("../input/shape.txt", (vertices + 3));
    input("../input/texture.txt", (colors + 3));
    input("../input/triangulation.txt", elements);
    for (int n = 0; n < COLORS_SIZE; n++) {
        colors[n] = colors[n] / 255.;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLint colorAttrib =  glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Calculate Transformation
    glm::mat4 model;
    model = glm::rotate(
      model,
      glm::radians(180.0f),       // degrees of rotation
      glm::vec3(0.0f, 0.0f, 1.0f) // axis of rotation
      );
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
/*
    glm::mat4 view = glm::lookAt(
      glm::vec3(0.0f, 0.0f, -2.0f), // position of camera
      glm::vec3(0.0f, 0.0f, 0.0f), // point to be centered on-screen
      glm::vec3(0.0f, 1.0f, 0.0f)  // up axis
      );
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
*/
    glm::mat4 proj = glm::perspective(
      glm::radians(45.0f), // vertical field of view
      800.0f / 600.0f,     // aspect ratio of screen
      1.0f,                // near clipping plane
      10.0f                // far clipping plane
      );
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));


    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Animation
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        glm::mat4 view = glm::lookAt(
          glm::vec3(0.0f, 0.0f, -3.0f + fmod(time, 4)), // position of camera
          glm::vec3(0.0f, 0.0f, 0.0f), // point to be centered on-screen
          glm::vec3(0.0f, 1.0f, 0.0f)  // up axis
          );
        GLint uniView = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

        /** DRAW HERE **/
        glDrawElements(GL_TRIANGLES, ELEMENTS_SIZE, GL_UNSIGNED_INT, 0);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }   glfwTerminate();
    return EXIT_SUCCESS;
}
