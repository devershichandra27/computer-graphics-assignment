#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

const double PI = 3.14159;

/* initial display-window size */
GLsizei winWidth = 400, winHeight = 400;
GLuint regHex;


void displayChild1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_POINTS);
	glColor3f()
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

void regHexagon(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glCallList(regHex);
	glFlush();
}
void winReshapeFcn(int newWidth, int newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) newWidth, 0.0, (GLdouble) newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Trial");
	//init();
	glutDisplayFunc(displayChild1);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	return 0;
}