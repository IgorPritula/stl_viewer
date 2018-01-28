#include <QtGui>
#include "mygldrawer.h"
#include "main.h"

int main(int argc, char *argv[])
{

    if(argc < 2)
    {
        std::cout << "Spesify the name of STL file.\n";
        return 1;
    }
    // get the name of the STL file (command line input)
    std::string STL_filename = argv[1];

    if(STL_filename.substr(STL_filename.find_last_of(".") + 1) != "stl") {
      std::cout << "File has wrong extension. Please, provide STL file.\n" << std::endl;
      return 1;
    }

    int error = read_ascii_STL_file(STL_filename,facet,x_min,x_max,y_min,y_max,z_min,z_max);
    // if something goes wrong, the above function will return a value of 1
    if (error == 1)
    {
        return 1;
    }
    float* vertices = new float[facet.size()*30];

    createVertexArray(facet, vertices);

    // calculate scaling factors along X, Y and Z
    float scale_x = (x_max - x_min)/2.0;
    float scale_y = (y_max - y_min)/2.0;
    float scale_z = (z_max - z_min)/2.0;

    float scale_0 = scale_x;
    if (scale_y > scale_0) scale_0 = scale_y;
    if (scale_z > scale_0) scale_0 = scale_z;
    float scale = 2.0 * scale_0;    // initial scale
    float scale_delta = 0.10 * scale_0;
    QApplication app(argc, argv);

    MyGLDrawer window;
    window.facet = facet;
    window.vertices = vertices; // need?
    window.scale = scale;
    window.scale_delta = scale_delta;
    window.x_min=x_min;
    window.x_max=x_max;
    window.y_min=y_min;
    window.y_max=y_max;
    window.z_min=z_min;
    window.z_max=z_max;
    window.setWindowTitle("STL viewer");
    window.setGeometry(100,100,500,500);
    window.show();
    window.setMouseTracking(true);
    return app.exec();

}
