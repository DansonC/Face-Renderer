// event_handler.cpp

#include "../include/event_handler.hpp"

void key_callback(GLFWwindow* window, 
										int key, 
										int scancode, 
										int action, 
										int mode) {

  if (action == GLFW_PRESS) {
      switch (key) {
      	case GLFW_KEY_ESCAPE:
      		glfwSetWindowShouldClose(mWindow, true);
      		break;
      	case GLFW_KEY_UP:
      		params.rot_x += ROT_SPEED;
      		break;
      	case GLFW_KEY_DOWN:
      		params.rot_x -= ROT_SPEED;
      		break;
      	case GLFW_KEY_LEFT:
      		params.rot_y -= ROT_SPEED;
      		break;
      	case GLFW_KEY_RIGHT:
      		params.rot_y += ROT_SPEED;
      		break;
      	case GLFW_KEY_LEFT_BRACKET:
      		params.rot_z -= ROT_SPEED;
      		break;
      	case GLFW_KEY_RIGHT_BRACKET:
      		params.rot_z += ROT_SPEED;
      		break;
      	case GLFW_KEY_KP_6:
      		params.camera_x += DEPTH_SPEED;
      		break;
      	case GLFW_KEY_KP_4:
      		params.camera_x -= DEPTH_SPEED;
      		break;
      	case GLFW_KEY_KP_2:
      		params.camera_y -= DEPTH_SPEED;
      		break;
      	case GLFW_KEY_KP_8:
      		params.camera_y += DEPTH_SPEED;
      		break;
      	case GLFW_KEY_KP_1:
      		params.camera_z -= DEPTH_SPEED;
      		break;
      	case GLFW_KEY_KP_3:
      		params.camera_z += DEPTH_SPEED;
      		break;
      	case GLFW_KEY_D:
      		params.focus_x += FOCUS_SPEED;
      		break;
      	case GLFW_KEY_A:
      		params.focus_x -= FOCUS_SPEED;
      		break;
      	case GLFW_KEY_X:
      		params.focus_y -= FOCUS_SPEED;
      		break;
      	case GLFW_KEY_W:
      		params.focus_y += FOCUS_SPEED;
      		break;
      	case GLFW_KEY_Z:
      		params.focus_z -= FOCUS_SPEED;
      		break;
      	case GLFW_KEY_C:
      		params.focus_z += FOCUS_SPEED;
      		break;
      	case GLFW_KEY_MINUS:
      		params.zoom = fmod(zoom + ZOOM_SPEED, 180);
      		break;
      	case GLFW_KEY_EQUAL:
      		params.zoom = fmod(zoom - ZOOM_SPEED, 180);
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
      		cout << "Saving " << time << ".png --implement";
      		break;
  	}
  }       
}

		
