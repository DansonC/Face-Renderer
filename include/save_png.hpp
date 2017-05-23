//output.hpp

#ifndef SAVE_PNG_HPP
#define SAVE_PNG_HPP

//-------------------//
//---   Headers   ---//
//-------------------//
// Renderer Headers
#include "../include/renderer.hpp"
//#include "../include/event_handler.hpp"

// System Headers
#include "../include/lodepng.h"
#include <string>

using namespace std;

//---------------------//
//---   Functions   ---//
//---------------------//
void save_png(string name);

#endif