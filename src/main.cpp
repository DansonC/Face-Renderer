// Local Headers
#include "nes.hpp"
#include "cpu.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>


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
    gladLoadGL();
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

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }   glfwTerminate();
    return EXIT_SUCCESS;
}
