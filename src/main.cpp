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

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <math.h>

// Support Headers
#include "../include/io.hpp"
#include "../include/event_handler.hpp"

//-----------------------------//
//---   OpenGL Constructs   ---//
//-----------------------------//
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

//---------------------------------//
//---   Initialize Parameters   ---//
//---------------------------------//
parameters params = parameters();

int main(int argc, char * argv[]) {
    if (argc == 1) {
        cout << "//-------------------------//\n"
                "//---   Face Renderer   ---//\n"
                "//-------------------------//\n";
        cout << "\nusage: ./face_render -h for and help\n";
    //} else { cout << argv[1] << endl; }
    } else if (argv[1][1] == 'h') {
        cout << "//-------------------------//\n"
                "//---   Face Renderer   ---//\n"
                "//-------------------------//\n"

                "\nCONTROLS\n"
                "Arrow Keys (up/down)\t\t\trotate model about x-axis\n"
                "Arrow Keys (left/right)\t\t\trotate model about y-axis\n"
                "Square Brackets (left/right)\t\trotate model about z-axis\n"
                "Minus and Plus(Equals)\t\t\tvertical field of view--zoom\n"
                "W A S D Keys\t\t\t\ttranslate focal point of camera--translate model\n"
                "Numpad 1 and 3\t\t\t\ttranslate camera position--move toward/away from model\n\n";
    }
    
    //auto t_start = std::chrono::high_resolution_clock::now();
    double start_time = glfwGetTime();
    double curr_time = start_time;
    double prev_time = start_time;
    double frame_time = 0.;
    const double MAX_FRAME_TIME = 1. / FRAME_RATE;

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
    GLFWwindow *mWindow = glfwCreateWindow(windowWidth, windowHeight, "Face Triangulation", nullptr, nullptr);

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
        // Keyboard Handler

        // Background Fill Color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Animation
        //auto t_now = std::chrono::high_resolution_clock::now();
        //double time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        prev_time = curr_time;
        curr_time = glfwGetTime();
        double delta_time = curr_time - prev_time;
        //frame_time += delta_time;
        handle_events(mWindow, params, delta_time);
        //if (frame_time >= MAX_FRAME_TIME) {
            //frame_time = 0.;
            //cout << "frame rate " << 1. / delta_time << endl;    

            // Calculate Transformation
            glm::mat4 view = glm::lookAt(
                     glm::vec3(params.camera_x, params.camera_y, params.camera_z),  // camera position
                     glm::vec3(params.focus_x, params.focus_y, params.focus_z),     // point to be centered on-screen
                     glm::vec3(0.0f, 1.0f, 0.0f)                                    // up vector
                    );
            GLint uniView = glGetUniformLocation(shaderProgram, "view");
            glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

            glm::mat4 model;
            model = glm::rotate(model, glm::radians(params.rot_x), glm::vec3(1.0f, 0.0f, 0.0f)); // rotation about x-axis
            model = glm::rotate(model, glm::radians(params.rot_y), glm::vec3(0.0f, 1.0f, 0.0f)); // rotation about y-axis
            model = glm::rotate(model, glm::radians(params.rot_z), glm::vec3(0.0f, 0.0f, 1.0f)); // rotation about z-axis        
            GLint uniModel = glGetUniformLocation(shaderProgram, "model");
            glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

            glm::mat4 proj = glm::perspective(
            glm::radians(params.vfov),  // vertical field of view 
            params.aspect,              // screen aspect ratio
            0.1f,                       // near clipping plane
            30.0f                       // far clipping plane
            );
            GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
            glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
        //}

        /** DRAW HERE **/
        glDrawElements(GL_TRIANGLES, ELEMENTS_SIZE, GL_UNSIGNED_INT, 0);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }   glfwTerminate();

    return EXIT_SUCCESS;
}
