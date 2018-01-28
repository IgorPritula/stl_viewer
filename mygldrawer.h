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
    float scale = 1;
    float scale_delta = 0.1;
    GLfloat rotationX = 0;
    GLfloat rotationY = 0;
    GLfloat rotationZ = 0;
    int rotationSpeed = 1;
    void drawGeometry();
    double max_tringle_area = 0.0;
    void getHistogramData();
    void drawHistogram();
    std::string display = "shape";
    static const std::string DISPLAY_SHAPE;
    static const std::string DISPLAY_HISTOGRAM;
    std::map<int, double> histogramData;
protected:
    int cax, cay, cbx, cby;
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    QPoint lastPos;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *me);
    void wheelEvent(QWheelEvent * event);
};

#endif // MYGLDRAWER_H
