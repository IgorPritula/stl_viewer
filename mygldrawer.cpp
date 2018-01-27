#include "mygldrawer.h"

MyGLDrawer::MyGLDrawer(QWidget *parent) : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer)); // Двойная буферизация
    //glDepthFunc(GL_LEQUAL); // Буфер глубины


}

void MyGLDrawer::initializeGL()
{
 // Work part of code.
          glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    initializeGLFunctions();//
    qglClearColor(Qt::black);//
    glShadeModel(GL_SMOOTH);//
    glEnable(GL_DEPTH_TEST);//
    glEnable(GL_CULL_FACE);//
    glEnable(GL_LIGHTING);//

    // свойства материала
    GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

    glEnable(GL_LIGHT0);  //
    GLfloat position[] = { 0.0, 0.0, 1.0, 0.0 };//
    glLightfv(GL_LIGHT0, GL_POSITION, position);//

    GLfloat light0_diffuse[] = {0.4, 0.7, 0.2};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);


}
void MyGLDrawer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    //glMatrixMode(GL_PROJECTION);
   // glLoadIdentity();
    //GLfloat x = (GLfloat)w / h;
    //glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    //glMatrixMode(GL_MODELVIEW);
}

void MyGLDrawer::paintGL()
{

    drawGeometry();

}

void MyGLDrawer::wheelEvent(QWheelEvent * event) {
    if (event->orientation() == Qt::Vertical) {
        int numDegrees = event->delta() / 8;
        int numSteps = numDegrees / 15;
        scale -= scale_delta * numSteps;
        updateGL();
    }
}

void MyGLDrawer::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLDrawer::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        GLfloat dx = (GLfloat)(event->x() - lastPos.x());
      GLfloat dy = (GLfloat)(event->y() - lastPos.y());
      rotationX = rotationX + (GLfloat)(dy / 2);
      if (rotationX > 90) rotationX = 90;
      if (rotationX < -90) rotationX = -90;
      rotationY = fmod(rotationY + (GLfloat)(dx / 2), 360);
      updateGL();
    }
    lastPos = event->pos();
}

void MyGLDrawer::drawGeometry() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(1.0/scale,1.0/scale,1.0/scale);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);

    glTranslatef(-(x_max + x_min)/2.0f,-(y_max + y_min)/2.0f,-(z_max + z_min)/2.0f);
    const int NUM_FACETS = facet.size();
    for (int i = 0; i < NUM_FACETS; ++i) {
      glLoadName(i);
      glBegin(GL_TRIANGLES);
      qglColor("blue");
      //glNormal3f(facet[i].normal.x, facet[i].normal.y, facet[i].normal.z);
      for (int j = 0; j < 3; ++j) {
        glNormal3f(facet[i].normal.x, facet[i].normal.y, facet[i].normal.z);
        glVertex3f(facet[i].point[j].x, facet[i].point[j].y, facet[i].point[j].z);
      }

      glEnd();
    }

}
