//ui.cpp

//-------------------//
//---   Headers   ---//
//-------------------//
// Renderer Headers
#include "../include/ui.hpp"


//---------------------//
//---   Functions   ---//
//---------------------//
void ui(GLFWwindow *mWindow, GLuint shaderProgram, parameters &params) {
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

    save_png("out.png");
}