// event_handler.hpp

#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

//-------------------//
//---   Headers   ---//
//-------------------//
// Renderer Headers
//#include "../include/renderer.hpp"

// System Headers
#include <GLFW/glfw3.h>

// Standard Headers
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;


//---------------------//
//---   Constants   ---//
//---------------------//
// Speed Constants
//const float ANIME_ROT_SPEED = 20.; 	// animated rotation speed
const float ROT_DEGREE = 150;        	    // keyboard input rotation speed
const float VFOV_DEGREE = 100;      	    // field of view angle--zoom sensitivity
const float DEPTH_INCR = 100;      		// depth field sensitivity
const float FOCUS_INCR = 75;     		// focus translation sensitivity
const float FRAME_RATE = 100; 			// seconds before update transformations

// Data Size                                            --- Fix Error Checking for Incorrect Data Size
const int VERTICES_SIZE = (53215 + 1) * 3; 
const int ELEMENTS_SIZE = 105840 * 3;
const int COLORS_SIZE = VERTICES_SIZE;
const int VIEWS_SIZE = 3;


//-------------------//
//---   Structs   ---//
//-------------------//
typedef struct Render_Parameters {
    // Rotations About Axis                                 --- Add Functionality for Roll, Pitch, Yaw
    float camera_x; 	// camera position x
    float camera_y; 	// camera position y
    float camera_z; 	// camera position z
    float focus_x; 		// camera point of focus x
    float focus_y; 		// camera point of focus y
    float focus_z; 		// camera point of focus z
    float rot_x; 		// degrees of rotation about x-axis
    float rot_y; 		// degrees of rotation about y-axis
    float rot_z; 		// degrees of rotation about y-axis

    float vfov;         // vertical field of view/zoom
    float aspect;       // aspect ratio (screenWidth / screenHeight)

    // Constructor
    Render_Parameters() :
	    camera_x  	(0.),
	    camera_y  	(0.),
	    camera_z  	(-20.),
	    focus_x 	(0.),
	    focus_y 	(0.),
	    focus_z 	(0.),
	    rot_x 		(0.),
	    rot_y 		(0.),
	    rot_z 		(0.),

	    vfov 		(8.),
	    //aspect 		(800. / 600.)
        aspect      ()
    {
    	// Initializations
    }
} parameters;


//---------------------//
//---   Functions   ---//
//---------------------//
void handle_events(GLFWwindow *mWindow, parameters &params, double delta);
/*
void key_callback(GLFWwindow *window, 
					int key, 
					int scancode, 
					int action, 
					int mode);
*/
#endif