#ifndef MYGLDRAWER_H
#define MYGLDRAWER_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QGLFunctions>
#include "vec_struct.h"

class MyGLDrawer : public QGLWidget, protected QGLFunctions
{
public:
    MyGLDrawer(QWidget *parent = 0);
    std::vector<triangle> facet;
    float* vertices;
    float x_min;
    float x_max;
    float y_min;
    float y_max;
    float z_min;
    float z_max;
    GLfloat rotationX = 0;
    GLfloat rotationY = 0;
    GLfloat rotationZ = 0;
    void drawGeometry();
protected:
    int cax, cay, cbx, cby;
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mouseMoveEvent(QMouseEvent *me);
};

#endif // MYGLDRAWER_H
