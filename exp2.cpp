#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define originalWidth 500.0
#define originalHeight 500.0

GLfloat defaultX=0.0, defaultY=0.0;
bool chooseOriginFlag = false,straightLineFlag = false;

void displayCanvas(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void straightLineFunction(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

void mouse (int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(chooseOriginFlag)
		{
			defaultX = (GLfloat)x/500.0;
			defaultY = (GLfloat)(y)/500.0;
			cout << defaultY << endl;
			chooseOriginFlag = false;
		}
		if(straightLineFlag)
		{
			straightLineFunction(defaultX, defaultY, (GLfloat)(x/500.0), (GLfloat)((y)/500.0));
			straightLineFlag = false;
			defaultX = x/500.0;
			defaultY = (y)/500.0;
		}
	}
}

enum MENU_ITEMS
{
	CHOOSE_ORIGIN,
	STRAIGHT_LINE,
};

//selecting default menu type
MENU_ITEMS show  = CHOOSE_ORIGIN;



//function to handle menu calls
static void menu(int item)
{
	switch(item)
	{
		case CHOOSE_ORIGIN:
		{
			chooseOriginFlag = true;
			break;
		}
		case STRAIGHT_LINE:
		{
			straightLineFlag = true;
			break;
		}
	}
	glutPostRedisplay();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(originalWidth, originalHeight);
	glutCreateWindow("Canvas");
	glutCreateMenu(menu);
		glutAddMenuEntry("Choose Origin", CHOOSE_ORIGIN);
		glutAddMenuEntry("Straight Line", STRAIGHT_LINE);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(displayCanvas);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}