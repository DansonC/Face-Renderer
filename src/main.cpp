//renderer.cpp

//-------------------//
//---   Headers   ---//
//-------------------//
// Renderer Headers
#include "../include/renderer.hpp"
#include "../include/io.hpp"
#include "../include/ui.hpp"
#include "../include/output.hpp"
#include "../include/save_png.hpp"


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


//-----------------------------//
//---   Terminal Messages   ---//
//-----------------------------//
void usage() {
    cout << "//-------------------------//\n"
            "//---   Face Renderer   ---//\n"
            "//-------------------------//\n";
    cout << "usage: ./face_render -h for and help\n\n";
}

void help() {
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


//----------------//
//---   Main   ---//
//----------------//
int main(int argc, char * argv[]) {
    // Terminal Messages
    int opt;
    while ( (opt = getopt(argc, argv, "h")) != -1 ) {
        switch (opt) {
            case 'h':
                help();
                return 0;
        }
    }
    usage();

    // OpenGL Window
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

    // Load Buffers
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
    vector<parameters> views;
    input("../input/shape.txt", (vertices + 3));
    input("../input/texture.txt", (colors + 3));
    input("../input/triangulation.txt", elements);
    input("../input/views.txt", views);
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

    // Occlusion Test
    glEnable(GL_DEPTH_TEST);

    // Output Image Files
    output(mWindow, shaderProgram, views);

    // User Interface
    ui(mWindow, shaderProgram, params);

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &color_buffer);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();

    return EXIT_SUCCESS;
}
