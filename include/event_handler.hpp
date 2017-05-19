// event_handler.hpp

#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

//---------------------//
//---   Constants   ---//
//---------------------//
// Speed Constants
const float ANIME_ROT_SPEED = 20.; // animated rotation speed
const float ROT_SPEED = 2.;        // keyboard input rotation speed
const float ZOOM_SPEED = 0.1;      // zoom sensitivity
const float DEPTH_SPEED = 10.;      // depth field sensitivity
const float FOCUS_SPEED = 0.1;     // focus translation sensitivity

// Data Size                                            --- Fix Error Checking for Incorrect Data Size
const int VERTICES_SIZE = (53215 + 1) * 3; 
const int ELEMENTS_SIZE = 105840 * 3;
const int COLORS_SIZE = VERTICES_SIZE;

//-------------------//
//---   Structs   ---//
//-------------------//
typedef struct Render_Parameters {
    // Rotations About Axis                                 --- Add Functionality for Roll, Pitch, Yaw
    float camera_x; 	// degrees of rotation about x-axis
    float camera_y; 	// degrees of rotation about y-axis
    float camera_z; 	// degrees of rotation about y-axis
    float focus_x; 		// degrees of rotation about x-axis
    float focus_y; 		// degrees of rotation about y-axis
    float focus_z; 		// degrees of rotation about y-axis
    float rot_x; 		// degrees of rotation about x-axis
    float rot_y; 		// degrees of rotation about y-axis
    float rot_z; 		// degrees of rotation about y-axis

    float zoom;         // zoom
    float aspect;       // aspect ratio

    // Constructor
    parameters() {
	    camera_x  	(0.), 			// degrees of rotation about x-axis
	    camera_y  	(0.), 			// degrees of rotation about y-axis
	    camera_z  	(-100.), 		// degrees of rotation about y-axis
	    focus_x 	(0.), 			// degrees of rotation about x-axis
	    focus_y 	(0.), 			// degrees of rotation about y-axis
	    focus_z 	(0.),			// degrees of rotation about y-axis
	    rot_x 		(0.), 			// degrees of rotation about x-axis
	    rot_y 		(0.), 			// degrees of rotation about y-axis
	    rot_z 		(0.), 			// degrees of rotation about y-axis

	    zoom 		(1),         	// zoom
	    aspect 		(800. / 600.)   // aspect ratio
    }
} parameters;


void key_callback(GLFWwindow *window, 
					int key, 
					int scancode, 
					int action, 
					int mode);

#endif