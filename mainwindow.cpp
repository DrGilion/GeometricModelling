#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    setFixedSize(400,400);
    mPix = QPixmap(400,400);
    mPix.fill(Qt::white);

    //set everything to false as nothing has started yet
    mousePressed = false;
    drawStarted = false;
}

void MainWindow::drawControlPoints(){
    /*glColor3fv(red);
    glPointSize(8.0);


    for(int i=0;i<num_points;i++){

      glBegin(GL_POINTS);
        glVertex3f((GLfloat)points[i].x,(GLfloat)points[i].y,(GLfloat)points[i].z);
      glEnd();
    }*/


}

void MainWindow::drawControlPointLine(){
    /*glColor3fv(black);
    glBegin(GL_LINE_STRIP);

    for(int i=0;i<num_points;i++){
       glVertex3f((GLfloat)points[i].x,(GLfloat)points[i].y,(GLfloat)points[i].z);
    }

    glEnd();*/
}

void MainWindow::drawBezierPolygon(){
    /*glColor3fv(blue);

    glBegin(GL_POLYGON);

    for(int i=0;i<num_points;i++)	{
        glVertex3f((GLfloat)points[i].x,(GLfloat)points[i].y,(GLfloat)points[i].z);
    }

    glEnd();*/

}

void MainWindow::drawCurve(){
/*
    glColor3fv(green);
    glBegin(GL_LINE_STRIP);

    for(int i=0;i<num_points;i++){
       glVertex3f((GLfloat)points[i].x,(GLfloat)points[i].y,(GLfloat)points[i].z);
    }

    glEnd();*/
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    std::cout << "x: " << event->localPos().x() << " y: " << event->localPos().y() << std::endl;
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    update();
}


/*int MainWindow::processHits (GLint hits, GLuint buffer[]){
   unsigned int i, j;
   GLuint ii, jj, names, *ptr;
   int result=-1;

   ptr = (GLuint *) buffer;
   for (i = 0; i < hits; i++) {
      names = *ptr;

      ptr++;
      ptr++;
      ptr++;

      for (j = 0; j < names; j++) {
      printf ("%d ", *ptr);

     result=(int)*ptr;

         ptr++;
      }
      printf ("\n");

   }
   return result;
}*/




/*int pickPoints(int x, int y){
    GLuint selectBuf[BUFSIZE];
    GLint hits;
    GLint viewport[4];

    glGetIntegerv (GL_VIEWPORT, viewport);
    glSelectBuffer (BUFSIZE, selectBuf);
    (void) glRenderMode(GL_SELECT);
        glInitNames();
        glPushName(0);

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();

    gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),8.0, 8.0, viewport);
    gluPerspective(60.0,(GLfloat) viewport[2] / (GLfloat) viewport[3], 1.0,20.0);
    drawControlPoints(GL_SELECT);

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();

    hits = glRenderMode (GL_RENDER);
    int result = processHits (hits, selectBuf);

    return result;
}*/

/*void mousePress(int button, int state, int x, int y){
    if((button == GLUT_LEFT_BUTTON)&&(state == GLUT_DOWN)) // && (glutGetModifiers()==GLUT_ACTIVE_CTRL))
       picked_pos=pickPoints(x,y);

    if((button == GLUT_LEFT_BUTTON)&&(state == GLUT_UP))
       picked_pos=-1;

    glutPostRedisplay();
}*/

/*void mouseMove(int x, int y){
     GLint viewport[4];
     glGetIntegerv(GL_VIEWPORT, viewport);
     GLfloat w=(GLfloat)viewport[2];
     GLfloat h=(GLfloat)viewport[3];

     GLint new_pos_x=x;
     GLint new_pos_y=viewport[3]-y;

     GLdouble cpm[16];
     glGetDoublev(GL_PROJECTION_MATRIX, cpm);

     GLdouble cmvm[16];
     glGetDoublev(GL_MODELVIEW_MATRIX, cmvm);

     GLdouble objx, objy, objz;
     GLfloat z;

     glReadPixels((GLdouble)new_pos_x,(GLdouble)new_pos_y,1, 1, GL_DEPTH_COMPONENT, GL_FLOAT,&z);
     gluUnProject((GLdouble)new_pos_x,(GLdouble)new_pos_y,z,cmvm,cpm,viewport,&objx,&objy,&objz);

     if(picked_pos>=0)
        points[picked_pos]=glm::vec3((double)objx,(double)objy,(double)objz);


     glutPostRedisplay();
}*/


void MainWindow::paintEvent(QPaintEvent* event){
    painter.begin(this);
    /*glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawBezierPolygon();
    drawControlPointLine();
    drawControlPoints(GL_RENDER);
    drawCurve();

    glutSwapBuffers();*/

    QPainter tempPainter(&mPix);
    tempPainter.setPen(QPen(Qt::black,10));
    tempPainter.drawPoint(QPoint(100,100));

    painter.drawPixmap(0,0,mPix);
    painter.end();
}

MainWindow::~MainWindow(){

}
