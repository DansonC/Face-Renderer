//save_png.cpp

//-------------------//
//---   Headers   ---//
//-------------------//
// Renderer Headers
#include "../include/save_png.hpp"


//---------------------//
//---   Functions   ---//
//---------------------//
void save_png(string name) {
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