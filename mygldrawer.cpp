#include "mygldrawer.h"

MyGLDrawer::MyGLDrawer(QWidget *parent) : QGLWidget(parent){}

const std::string MyGLDrawer::DISPLAY_SHAPE = "shape";
const std::string MyGLDrawer::DISPLAY_HISTOGRAM = "histogram";

void MyGLDrawer::initializeGL()
{
    getHistogramData();

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    initializeGLFunctions();
    qglClearColor(Qt::white);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);//

    glEnable(GL_LIGHT0);
    GLfloat position[] = { 0.0, 0.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, position);

}
void MyGLDrawer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

}

void MyGLDrawer::paintGL()
{
    if (display == DISPLAY_SHAPE) {
        glEnable(GL_LIGHTING);
        drawGeometry();
    }
    if (display == DISPLAY_HISTOGRAM) {
       glDisable(GL_LIGHTING);
       drawHistogram();
    }

}

void MyGLDrawer::wheelEvent(QWheelEvent * event) {
    if(display == DISPLAY_HISTOGRAM) {
        return;
    }
    if (event->orientation() == Qt::Vertical) {
        int numDegrees = event->delta() / 8;
        int numSteps = numDegrees / 15;
        scale -= scale_delta * numSteps;
        updateGL();
    }
}

void MyGLDrawer::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        lastPos = event->pos();
    }
    if (event->buttons() & Qt::RightButton) {
        if (display == DISPLAY_SHAPE) {
            display = DISPLAY_HISTOGRAM;
        }
        else  {
            display = DISPLAY_SHAPE;
        }
        updateGL();
    }

}

void MyGLDrawer::mouseMoveEvent(QMouseEvent *event)
{
    if(display == DISPLAY_HISTOGRAM) {
        return;
    }
    if (event->buttons() & Qt::LeftButton) {
        GLfloat dx = (GLfloat)(event->x() - lastPos.x());
        GLfloat dy = (GLfloat)(event->y() - lastPos.y());
        rotationX = rotationX - (GLfloat)(dy / 2);
        if (rotationX > 90) rotationX = 90;
        if (rotationX < -90) rotationX = -90;
        rotationY = fmod(rotationY - (GLfloat)(dx / 2), 360);
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
      glNormal3f(facet[i].normal.x, facet[i].normal.y, facet[i].normal.z);
      for (int j = 0; j < 3; ++j) {
        glVertex3f(facet[i].point[j].x, facet[i].point[j].y, facet[i].point[j].z);
      }
      glEnd();
    }
}

void MyGLDrawer::getHistogramData() {
    double axleZ[3] = {0.0, 0.0, 1.0};

    std::map<int, double> degrees_count;
    for(int i = 0; i < facet.size(); i++) {
        double nx = facet[i].normal.x;
        double ny = facet[i].normal.y;
        double nz = facet[i].normal.z;
        double scal = nx * axleZ[0] + ny * axleZ[1] + nz * axleZ[2];
        double axleL = sqrt(pow(axleZ[0],2) + pow(axleZ[1],2) + pow(axleZ[2], 2));
        double nL = sqrt(pow(nx,2) + pow(ny,2) + pow(nz,2));
        double cosL = scal / (axleL * nL);

        int degrees = (int)(acos (cosL) * 180.0 / M_PI);
        degrees = 90 - degrees;

        double area = sqrt(pow(nx,2) + pow(ny,2) + pow(nz, 2)) / 2;

        if (degrees_count.find(degrees) == degrees_count.end()) {
            degrees_count[degrees] = area;
        }
        else {
            degrees_count[degrees] += area;
        }

        if(degrees_count[degrees] > max_tringle_area) {
            max_tringle_area = degrees_count[degrees];
        }
    }

    histogramData = degrees_count;
}

void MyGLDrawer::drawHistogram() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.99f, -0.99f);
        glVertex2f( 0.99f, -0.99f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.99f, -0.99f);
        glVertex2f(-0.99f, 0.99f);
    glEnd();

    for (const auto& elem : histogramData) {
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f((float)elem.first * 0.01f, -0.99f);    // x, y
            glVertex2f((float)elem.first * 0.01f, (elem.second / (max_tringle_area / 0.99f)) - 0.99f);
        glEnd();
    }
}

