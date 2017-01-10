// Local Headers
#include "nes.h"
#include "cpu.h"
// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>

#define SCREEN_WIDTH 4
#define SCREEN_HEIGHT 4
#define PIXEL_SIZE 2
#define SCREEN_OFFSET 0


const GLchar* vertexSource =
    "#version 150 core\n"
    "in vec2 position;"
    "void main()"
    "{"
    "    gl_Position = vec4(position, 0.0, 1.0);"
    "}";
const GLchar* fragmentSource =
    "#version 150 core\n"
    "out vec4 outColor;"
    "void main()"
    "{"
    "    outColor = vec4(1.0, 1.0, 1.0, 1.0);"
    "}";

GLfloat vertices[SCREEN_WIDTH + 1][SCREEN_HEIGHT + 1][2];
void fill_vertices() {
    for(int i = 0; i < SCREEN_WIDTH + 1; i++)
    {
        for(int j = 0; j < SCREEN_HEIGHT + 1; j++)
        {
            vertices[i][j][0] = i;
            vertices[i][j][1] = j;
            vertices[i][j][0] = vertices[i][j][0] * 2 / SCREEN_WIDTH - 1;
            vertices[i][j][1] = vertices[i][j][1] * 2 / SCREEN_HEIGHT - 1;
        }
    }
}

GLuint elements[SCREEN_WIDTH][SCREEN_HEIGHT][6];

GLfloat colors[SCREEN_WIDTH + 1][SCREEN_HEIGHT + 1][2];

void fill_elements() {
    for(int i = 0; i < SCREEN_WIDTH; i++) {
        for(int j = 0; j < SCREEN_HEIGHT; j++)
        {
            elements[i][j][0] = i * SCREEN_HEIGHT + j;
            elements[i][j][1] = i * SCREEN_HEIGHT + j + 1;
            elements[i][j][2] = (i + 1) * SCREEN_HEIGHT + j;
            elements[i][j][3] = (i + 1) * SCREEN_HEIGHT + j;
            elements[i][j][4] = (i + 1) * SCREEN_HEIGHT + j + 1;
            elements[i][j][5] = i * SCREEN_HEIGHT + j;
        }
    }
}
/** Print's usage information **/
void usage() {
    printf("nes-emu <rom path>\n");
}
int main(int argc, char * argv[]) {

    if (argc == 2) {
      char* secondArg = argv[1];
      fprintf(stderr, "%s loading...\n", secondArg);
    }
    else {
        usage();
        return EXIT_FAILURE;
    }
    
    int windowWidth = 500; // mWidth for full window
    int windowHeight = 500; // mHeight for full window

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(windowWidth, windowHeight, "NES Emulator", nullptr, nullptr);

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
    
        
    fill_vertices();
    fill_elements();
    
    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    
    GLuint color_buffer;
    glGenBuffers(1, &color_buffer);
    

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    //Todo change to GL_STREAM_DRAW
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    //Todo change to GL_STREAM_DRAW
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Create Element Array
    GLuint ebo;
    glGenBuffers(1, &ebo);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertexSource, NULL);
    glCompileShader(vertex_shader);
    
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragmentSource, NULL);
    glCompileShader(fragment_shader);
    
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glBindFragDataLocation(program, 0, "outColor");
    glLinkProgram(program);
    glUseProgram(program);
    
    GLint posAttrib = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    // fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
    fprintf(stderr, "NES Emulator loaded\n");
    
    NesCPU* cpu = new NesCPU(argv[1]);

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        /** DRAW HERE **/
        glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_INT, 0);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }   glfwTerminate();
    return EXIT_SUCCESS;
}
