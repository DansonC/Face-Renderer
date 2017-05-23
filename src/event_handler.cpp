// event_handler.cpp

//-------------------//
//---   Headers   ---//
//-------------------//
// Renderer Headers
#include "../include/event_handler.hpp"


//---------------------//
//---   Functions   ---//
//---------------------//
void handle_events(GLFWwindow *mWindow, parameters &params, double delta) {
      // Keyboard Event Handling                                         ---READ KEY and SWITCH TABLE FUNCTION
  if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(mWindow, true);

  if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS)
    params.rot_x += ROT_DEGREE * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
    params.rot_x -= ROT_DEGREE * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
    params.rot_y -= ROT_DEGREE * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
    params.rot_y += ROT_DEGREE * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
    params.rot_z -= ROT_DEGREE * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
    params.rot_z += ROT_DEGREE * delta;

  if (glfwGetKey(mWindow, GLFW_KEY_KP_6) == GLFW_PRESS)
    params.camera_x += DEPTH_INCR * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_KP_4) == GLFW_PRESS)
    params.camera_x -= DEPTH_INCR * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_KP_2) == GLFW_PRESS)
    params.camera_y -= DEPTH_INCR * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_KP_8) == GLFW_PRESS)
    params.camera_y += DEPTH_INCR * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_KP_1) == GLFW_PRESS)
    params.camera_z -= DEPTH_INCR * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_KP_3) == GLFW_PRESS)
    params.camera_z += DEPTH_INCR * delta;

  if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
    params.focus_x += FOCUS_INCR * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
    params.focus_x -= FOCUS_INCR * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
    params.focus_y -= FOCUS_INCR * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
    params.focus_y += FOCUS_INCR * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_Z) == GLFW_PRESS)
    params.focus_z -= FOCUS_INCR * delta;
  if (glfwGetKey(mWindow, GLFW_KEY_C) == GLFW_PRESS)
    params.focus_z += FOCUS_INCR * delta;


  if (glfwGetKey(mWindow, GLFW_KEY_MINUS) == GLFW_PRESS)
    params.vfov = fmod(params.vfov + VFOV_DEGREE * delta, 180.);
  if (glfwGetKey(mWindow, GLFW_KEY_EQUAL) == GLFW_PRESS)
    params.vfov = fmod(params.vfov - VFOV_DEGREE * delta, 180.);

  if (glfwGetKey(mWindow, GLFW_KEY_COMMA) == GLFW_PRESS)
    params.aspect += 0.1;
  if (glfwGetKey(mWindow, GLFW_KEY_PERIOD) == GLFW_PRESS)
    params.aspect -= 0.1;

  //if (glfwGetKey(mWindow, GLFW_KEY_P) == GLFW_RELEASE)
    //cout << "Saving .png --implement";
}

/*
void key_callback(GLFWwindow* window, 
										int key, 
										int scancode, 
										int action, 
										int mode) {

  if (action == GLFW_PRESS) {
      switch (key) {
      	case GLFW_KEY_ESCAPE:
      		glfwSetWindowShouldClose(window, true);
      		break;
      	case GLFW_KEY_UP:
      		params.rot_x += ROT_DEGREE;
      		break;
      	case GLFW_KEY_DOWN:
      		params.rot_x -= ROT_DEGREE;
      		break;
      	case GLFW_KEY_LEFT:
      		params.rot_y -= ROT_DEGREE;
      		break;
      	case GLFW_KEY_RIGHT:
      		params.rot_y += ROT_DEGREE;
      		break;
      	case GLFW_KEY_LEFT_BRACKET:
      		params.rot_z -= ROT_DEGREE;
      		break;
      	case GLFW_KEY_RIGHT_BRACKET:
      		params.rot_z += ROT_DEGREE;
      		break;
      	case GLFW_KEY_KP_6:
      		params.camera_x += DEPTH_INCR;
      		break;
      	case GLFW_KEY_KP_4:
      		params.camera_x -= DEPTH_INCR;
      		break;
      	case GLFW_KEY_KP_2:
      		params.camera_y -= DEPTH_INCR;
      		break;
      	case GLFW_KEY_KP_8:
      		params.camera_y += DEPTH_INCR;
      		break;
      	case GLFW_KEY_KP_1:
      		params.camera_z -= DEPTH_INCR;
      		break;
      	case GLFW_KEY_KP_3:
      		params.camera_z += DEPTH_INCR;
      		break;
      	case GLFW_KEY_D:
      		params.focus_x += FOCUS_INCR;
      		break;
      	case GLFW_KEY_A:
      		params.focus_x -= FOCUS_INCR;
      		break;
      	case GLFW_KEY_X:
      		params.focus_y -= FOCUS_INCR;
      		break;
      	case GLFW_KEY_W:
      		params.focus_y += FOCUS_INCR;
      		break;
      	case GLFW_KEY_Z:
      		params.focus_z -= FOCUS_INCR;
      		break;
      	case GLFW_KEY_C:
      		params.focus_z += FOCUS_INCR;
      		break;
      	case GLFW_KEY_MINUS:
      		params.vfov = fmod(params.vfov + VFOV_DEGREE, 180);
      		break;
      	case GLFW_KEY_EQUAL:
      		params.vfov = fmod(params.vfov - VFOV_DEGREE, 180);
      		break;
      	case GLFW_KEY_COMMA:
      		params.aspect += 0.1;
      		break;
      	case GLFW_KEY_PERIOD:
      		params.aspect -= 0.1;
      		break;
     	}
  }

  if (action == GLFW_RELEASE) {
  	switch (key) {
      	case GLFW_KEY_P:
      		cout << "Saving .png --implement";
      		break;
  	}
  }       
}
*/

		
