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

// Rotations About Axis                                 --- Add Functionality for Roll, Pitch, Yaw
float camera_x = 0.; // degrees of rotation about x-axis
float camera_y = 0.; // degrees of rotation about y-axis
float camera_z = -3.; // degrees of rotation about y-axis
float focus_x = 0.; // degrees of rotation about x-axis
float focus_y = 0.; // degrees of rotation about y-axis
float focus_z = 0.; // degrees of rotation about y-axis
float x = 0.; // degrees of rotation about x-axis
float y = 0.; // degrees of rotation about y-axis
float z = 0.; // degrees of rotation about y-axis
const float ANIME_ROT_SPEED = 20.; // animated rotation speed
const float ROT_SPEED = 2.;        // keyboard input rotation speed
const float INCREMENT = 0.1;
float zoom = 45.;                  // zoom
float aspect = 800. / 600.;        // aspect ratio

// Data Size                                            --- Fix Error Checking for Incorrect Data Size
const int VERTICES_SIZE = (53215 + 1) * 3; 
const int ELEMENTS_SIZE = 105840 * 3;
const int COLORS_SIZE = VERTICES_SIZE;

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

int main(int argc, char * argv[]) {

    auto t_start = std::chrono::high_resolution_clock::now();

    int windowWidth = 800;
    int windowHeight = 600;

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

    // Load Data From File
    GLfloat vertices[VERTICES_SIZE];
    GLfloat colors[COLORS_SIZE];
    GLuint elements[ELEMENTS_SIZE];
    input("../input/shape.txt", (vertices + 3));
    input("../input/texture.txt", (colors + 3));
    input("../input/triangulation.txt", elements);
    // Shift Texture Map for 1-Indexing
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

    // Add Occlusion Test
    glEnable(GL_DEPTH_TEST);

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {

        // Keyboard Event Handling                                         ---READ KEY and SWITCH TABLE FUNCTION
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS)
            x += ROT_SPEED;
        if (glfwGetKey(mWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
            x -= ROT_SPEED;
        if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
            y -= ROT_SPEED;
        if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
            y += ROT_SPEED;
        if (glfwGetKey(mWindow, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
            z -= ROT_SPEED;
        if (glfwGetKey(mWindow, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
            z += ROT_SPEED;

        if (glfwGetKey(mWindow, GLFW_KEY_KP_6) == GLFW_PRESS)
            camera_x += INCREMENT;
        if (glfwGetKey(mWindow, GLFW_KEY_KP_4) == GLFW_PRESS)
            camera_x -= INCREMENT;
        if (glfwGetKey(mWindow, GLFW_KEY_KP_2) == GLFW_PRESS)
            camera_y -= INCREMENT;
        if (glfwGetKey(mWindow, GLFW_KEY_KP_8) == GLFW_PRESS)
            camera_y += INCREMENT;
        if (glfwGetKey(mWindow, GLFW_KEY_KP_1) == GLFW_PRESS)
            camera_z -= INCREMENT;
        if (glfwGetKey(mWindow, GLFW_KEY_KP_3) == GLFW_PRESS)
            camera_z += INCREMENT;

        if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
            focus_x += INCREMENT;
        if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
            focus_x -= INCREMENT;
        if (glfwGetKey(mWindow, GLFW_KEY_X) == GLFW_PRESS)
            focus_y -= INCREMENT;
        if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
            focus_y += INCREMENT;
        if (glfwGetKey(mWindow, GLFW_KEY_Z) == GLFW_PRESS)
            focus_z -= INCREMENT;
        if (glfwGetKey(mWindow, GLFW_KEY_C) == GLFW_PRESS)
            focus_z += INCREMENT;


        if (glfwGetKey(mWindow, GLFW_KEY_MINUS) == GLFW_PRESS)
            zoom = fmod(zoom + ROT_SPEED, 180);
        if (glfwGetKey(mWindow, GLFW_KEY_EQUAL) == GLFW_PRESS)
            zoom = fmod(zoom - ROT_SPEED, 180);

        if (glfwGetKey(mWindow, GLFW_KEY_COMMA) == GLFW_PRESS)
            aspect += 0.1;
        if (glfwGetKey(mWindow, GLFW_KEY_PERIOD) == GLFW_PRESS)
            aspect -= 0.1;
        

        // Animation
        //auto t_now = std::chrono::high_resolution_clock::now();
        //float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        //y = fmod(time * ROT_SPEED, 360);

        // Background Fill Color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Calculate Transformation
        glm::mat4 view = glm::lookAt(
                 glm::vec3(camera_x, camera_y, camera_z), // camera position
                 glm::vec3(focus_x, focus_y, focus_z),  // point to be centered on-screen
                 glm::vec3(0.0f, 1.0f, 0.0f)   // up vector
                );
        GLint uniView = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));


        glm::mat4 model;
        model = glm::rotate(model, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f)); // rotation about x-axis
        model = glm::rotate(model, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f)); // rotation about y-axis
        model = glm::rotate(model, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f)); // rotation about z-axis        
        GLint uniModel = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 proj = glm::perspective(
        glm::radians(zoom),   // vertical field of view 
        aspect,               // screen aspect ratio
        0.1f,                 // near clipping plane
        100.0f                // far clipping plane
        );
        GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
        glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

        /** DRAW HERE **/
        glDrawElements(GL_TRIANGLES, ELEMENTS_SIZE, GL_UNSIGNED_INT, 0);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }   glfwTerminate();

    return EXIT_SUCCESS;
}
