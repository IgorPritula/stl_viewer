#include <QtGui>
#include "mygldrawer.h"
#include "main.h"

int main(int argc, char *argv[])
{

    if(argc < 2)
        {
            std::cout << "Spesify the name of STL file\n";
            return 1;
        }
    // get the name of the STL file (command line input)
    std::string STL_filename = argv[1];

    int error = read_ascii_STL_file(STL_filename,facet,x_min,x_max,y_min,y_max,z_min,z_max);

    // if something goes wrong, the above function will return a value of 1
    if (error == 1)
    {
        return(1);// exit returning an error
    }
    float* vertices = new float[facet.size()*30];

    createVertexArray(facet, vertices);


    QApplication app(argc, argv);

    MyGLDrawer window;
    window.facet = facet;
    window.vertices = vertices;
    window.x_min=x_min;
    window.x_max=x_max;
    window.y_min=y_min;
    window.y_max=y_max;
    window.z_min=z_min;
    window.z_max=z_max;
    window.setWindowTitle("QT OpenGL - Lesson 1");
    window.setGeometry(100,100,500,500);
    window.show();
    window.setMouseTracking(true);
    return app.exec();

}
