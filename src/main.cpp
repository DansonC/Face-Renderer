//renderer.cpp

//-------------------//
//---   Headers   ---//
//-------------------//
// Renderer Headers
#include "../include/FaceRenderer3D.hpp"
#include "../include/io.hpp"


//-----------------------------//
//---   OpenGL Constructs   ---//
//-----------------------------//


//-----------------------------//
//---   Terminal Messages   ---//
//-----------------------------//
void usage() {
    cout << "//-------------------------//\n"
            "//---   Face Renderer   ---//\n"
            "//-------------------------//\n";
    cout << "usage: ./FaceRender3D -h for and help\n\n"
            "\t\t./FaceRenderer3D -o to output .png image set in output directory\n"
            "\t\talso, an out.png will be saved in the current directory upon exit of ui\n\n";
}

void help() {
    cout << "//-------------------------//\n"
            "//---   Face Renderer   ---//\n"
            "//-------------------------//\n"

            "\nCONTROLS\n"
            "Arrow Keys (up/down)\t\t\trotate model about x-axis\n"
            "Arrow Keys (left/right)\t\t\trotate model about y-axis\n"
            "Square Brackets (left/right)\t\trotate model about z-axis\n"
            "Minus and Plus(Equals)\t\t\tvertical field of view--zoom\n"
            "W A S D Keys\t\t\t\ttranslate focal point of camera--translate model\n"
            "Numpad 1 and 3\t\t\t\ttranslate camera position--move toward/away from model\n\n";
}


//----------------//
//---   Main   ---//
//----------------//
int main(int argc, char * argv[]) {
    // Terminal Messages
    bool output_png = false;
    int opt;
    string directory;
    while ( (opt = getopt(argc, argv, "ho:")) != -1 ) {
        switch (opt) {
            case 'h':
                help();
                return EXIT_SUCCESS;
            case 'o':
                output_png = true;
                directory = optarg;
        }
    }
    usage();

    // Load Data From File
    GLfloat vertices[VERTICES_SIZE];
    GLfloat colors[COLORS_SIZE];
    GLuint elements[ELEMENTS_SIZE];
    vector<parameters> views;
    input("../input/shape.txt", (vertices + 3));
    input("../input/texture.txt", (colors + 3));
    input("../input/triangulation.txt", elements);
    input("../input/views.txt", views);
    // Shift Texture Map for 1-Indexing
    for (int n = 0; n < COLORS_SIZE; n++) {
        colors[n] = colors[n] / 255.;
    }

    FaceRenderer* renderer = new FaceRenderer(vertices, colors, elements, VERTICES_SIZE, COLORS_SIZE, ELEMENTS_SIZE);
    if(renderer->init() == EXIT_FAILURE)
        return EXIT_FAILURE;

    // Output Image Files
    //renderer->output(views, directory);


    // User Interface
    renderer->ui();
    renderer->destroy();

    return EXIT_SUCCESS;
}
