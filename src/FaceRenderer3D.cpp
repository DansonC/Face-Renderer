//FaceRenderer3D.cpp

//-------------------//
//---   Headers   ---//
//-------------------//

// Renderer Headers
#include "../include/FaceRenderer3D.hpp"
//---------------------// //---   Functions   ---//
//---------------------//


FaceRenderer::FaceRenderer(GLfloat* vert, GLfloat* col, GLuint* elem, int num_vert, int num_col, int num_elem)
{

    //---------------------------------//
    //---   Initialize Parameters   ---//
    //---------------------------------//
    params= parameters();


    vertices = vert;
    colors = col;
    elements = elem;
    vertices_size = num_vert;
    colors_size = num_col;
    elements_size = num_elem;
}

int FaceRenderer::init()
{

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
    mWindow = glfwCreateWindow(windowWidth, windowHeight, "Face Triangulation", nullptr, nullptr);

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
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);

    glGenBuffers(1, &color_buffer);

    glGenBuffers(1, &ebo);



    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements_size * sizeof(GLuint), elements, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    shaderProgram = glCreateProgram();
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
    glBufferData(GL_ARRAY_BUFFER, colors_size * sizeof(GLfloat), colors, GL_STATIC_DRAW);

    GLint colorAttrib =  glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Occlusion Test
    glEnable(GL_DEPTH_TEST);
    return EXIT_SUCCESS;
}

void FaceRenderer::destroy()
{

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &color_buffer);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();

}
void FaceRenderer::output(vector<parameters> &views, string directory) {
    for (unsigned int i = 0; i < VIEWS_SIZE; i++) {
        // Set Parameters
        parameters params = views[i];
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

        // Background Fill Color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // DRAW HERE
        glDrawElements(GL_TRIANGLES, ELEMENTS_SIZE, GL_UNSIGNED_INT, 0);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();

        string filename = "../output/";
        filename.append(to_string(i));
        filename.append(".png");
        save_png(filename);
        cout << filename << ": " << views[i].rot_x << "\t" << views[i].rot_y << "\t" << views[i].rot_z << endl;
    }
}

void FaceRenderer::ui() {

    //unsigned int image_w, image_h;
    //unsigned char* image =  load_png("bg.png", &image_w, &image_h);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_w, image_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    params.aspect = windowWidth / windowHeight;

    //auto t_start = std::chrono::high_resolution_clock::now();
    double start_time = glfwGetTime();
    double curr_time = start_time;
    double prev_time = start_time;
    //double frame_time = 0.;
    //const double MAX_FRAME_TIME = 1. / FRAME_RATE;

	while (glfwWindowShouldClose(mWindow) == false) {
        // Animation
        //auto t_now = std::chrono::high_resolution_clock::now();
        //double time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        // Keyboard Handler
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

        // Background Fill Color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // DRAW HERE
        glDrawElements(GL_TRIANGLES, ELEMENTS_SIZE, GL_UNSIGNED_INT, 0);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
}

void FaceRenderer::save_png(string name) {
    // Output Image File
    GLubyte *pixels_flipped = (GLubyte*)malloc(4 * sizeof(GLubyte) * windowWidth * windowHeight);
    GLubyte *pixels = (GLubyte*)malloc(4 * sizeof(GLubyte) * windowWidth * windowHeight);
    glReadPixels(0, 0, windowWidth, windowHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels_flipped);

    for(int i = 0; i < windowHeight; i++) {
        for(int j = 0; j < windowWidth; j++) {
            for(int k = 0; k < 4; k++)
	           pixels[(j + i * windowWidth) * 4 + k] = pixels_flipped[(j + (windowHeight - i) * windowWidth) * 4 + k];
	    }
    }
    
    lodepng::encode(name, (unsigned char*) pixels, windowWidth, windowHeight);
    free(pixels);
    free(pixels_flipped);
}
