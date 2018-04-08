#include <QApplication>
#include <QPushButton>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>

#include "mainwindow.h"

#if !defined(BUFSIZE)
#define BUFSIZE 512
#endif

using namespace std;

int num_points=4;
//glm::vec3* points = new glm::vec3[num_points];
//glm::vec3 translationVector;
//vector<glm::vec3> bezierPoints;
int picked_pos=-1;

const float white[] = {1.0, 1.0, 1.0};
const float black[] = {0.0, 0.0, 0.0};
const float red[] = {1.0, 0.0, 0.0};
const float green[] = {0.0, 1.0, 0.0};
const float blue[] = {0.0, 0.0, 1.0};

/*class BezierStruct{

};

void plotBezier(vector<glm::vec3> pointsToDraw, int k){

}

void drawControlPoints(GLenum mode){
    glColor3fv(red);
	glPointSize(8.0);
	

    for(int i=0;i<num_points;i++){
	  if(mode==GL_SELECT)
	    glLoadName(i);
	  glBegin(GL_POINTS);
        glVertex3f((GLfloat)points[i].x,(GLfloat)points[i].y,(GLfloat)points[i].z);
	  glEnd();
	}
	
	if(mode==GL_SELECT)
	    glPopName();


}

void drawControlPointLine(){
    glColor3fv(black);
    glBegin(GL_LINE_STRIP);

    for(int i=0;i<num_points;i++){
       glVertex3f((GLfloat)points[i].x,(GLfloat)points[i].y,(GLfloat)points[i].z);
    }

    glEnd();
}

void drawBezierPolygon(){
    glColor3fv(blue);

    glBegin(GL_POLYGON);

    for(int i=0;i<num_points;i++)	{
        glVertex3f((GLfloat)points[i].x,(GLfloat)points[i].y,(GLfloat)points[i].z);
    }

    glEnd();

}

void drawCurve(){

    glColor3fv(green);
    glBegin(GL_LINE_STRIP);

    for(int i=0;i<num_points;i++){
       glVertex3f((GLfloat)points[i].x,(GLfloat)points[i].y,(GLfloat)points[i].z);
    }

    glEnd();
}


int processHits (GLint hits, GLuint buffer[]){
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
}




int pickPoints(int x, int y){
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
}

void mousePress(int button, int state, int x, int y){
    if((button == GLUT_LEFT_BUTTON)&&(state == GLUT_DOWN)) // && (glutGetModifiers()==GLUT_ACTIVE_CTRL))
       picked_pos=pickPoints(x,y);

    if((button == GLUT_LEFT_BUTTON)&&(state == GLUT_UP))
       picked_pos=-1;

    glutPostRedisplay();
}

void mouseMove(int x, int y){
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
}


void display(void){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawBezierPolygon();
    drawControlPointLine();
    drawControlPoints(GL_RENDER);
    drawCurve();

    glutSwapBuffers();
}

void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_FLAT);
    points[0]=glm::vec3(-1.0,0.0,0.0);
    points[1]=glm::vec3(-1.0,1.0,0.0);
    points[2]=glm::vec3(1.0,1.0,0.0);
    points[3]=glm::vec3(1.0,0.0,0.0);

	 
}

void reshape(GLsizei w, GLsizei h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat) w / (GLfloat) h, 1.0,20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
}


void keyboard(unsigned char key, int x, int y){
    switch(key) {

	case 's':   
           // do something
            glutPostRedisplay();
	    break;
	case 'i':
		// do something
           glutPostRedisplay();
	    break;
	case 'c':   
         // do something
            glutPostRedisplay();
	    break;
	case 'y':
	    // do something
            glutPostRedisplay();
	    break;
	case 'z':
	    // do something
            glutPostRedisplay();
	    break;

	}
	
}*/

int main(int argc, char** argv){
    /*glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 600, 360 );
    glutCreateWindow( "GM Uebung SoSe 2018" );

    init();*/
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    /*glutMouseFunc(mousePress);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
	
    glutMainLoop();*/

    return app.exec();
}
