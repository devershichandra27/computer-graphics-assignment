#include <GL/glut.h>
#include <math.h>
#include <iostream>
#define PI 3.14159

using namespace std;

void displayChild1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_POINTS);
	float r = 0.8, x, y;
	for (double i = 0; i < PI/2; i+=0.001)
	{
		x = 0.8*cos(i);
		y = 0.8*sin(i);
		glVertex2f(x,y);
		glVertex2f(-x,-y);
		glVertex2f(-x,y);
		glVertex2f(x,-y);
	}
		
	glEnd();
	glFlush();
}
void displayChild2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1,1,1,1);
	glBegin(GL_POINTS);
	float r = 50, x=0, y=r;
	cout << -y <<endl;
	float h = 1-r;
	while(y>x)
	{
			glVertex2f(x,y);
			glVertex2f(-x,y);
			glVertex2f(-y,x);
			glVertex2f(-y, -x);
			glVertex2f(-x,-y);
			glVertex2f(x, -y);
			glVertex2f(y, -x);
			glVertex2f(y,x);
		if(h<0)
			h += 2*x +3;
		else
		{
			h += 2*(x-y)+5;
			y-=1;
		}
		x+=1;
	}
	glEnd();
	glFlush();
}

void winReshapeFcn (int newWidth, int newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D((GLdouble)-(newWidth)/2,(GLdouble)(newWidth)/2, (GLdouble)-(newHeight)/2, (GLdouble)(newHeight)/2 );
	//gluOrtho2D(0.0,(GLdouble)(newWidth), 0.0, (GLdouble)(newHeight) );
	glClear(GL_COLOR_BUFFER_BIT);
}

void myinit()
{
	glViewport(0,0,500, 500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0,100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	int mainWindow = glutCreateWindow("Hello World!");
	//glutDisplayFunc(displayParent);
	
	//top left subwindow
	//glutCreateSubWindow(mainWindow, 0, 0, 150, 150);
	glutDisplayFunc(displayChild2);
	glutReshapeFunc(winReshapeFcn);
	myinit();
	//bottom right subwindow
	//glutCreateSubWindow(mainWindow, 150, 0, 150, 150);
	//glutDisplayFunc(displayMe);	
	//glClearColor(0,0,1,1);

	glutMainLoop();
	return 0;
}