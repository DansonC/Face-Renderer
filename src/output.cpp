//output.cpp

//-------------------//
//---   Headers   ---//
//-------------------//

// Renderer Headers
#include "../include/output.hpp"


//---------------------//
//---   Functions   ---//
//---------------------//
void output(GLFWwindow *mWindow, GLuint shaderProgram, vector<parameters> &views) {
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