#include <GL/glut.h>
#include <iostream>
#include <math.h>

#define originalWidth 500
#define originalHeight 500

using namespace std;
bool floodFillFlag = false, boundaryFillflag = false;

 struct Color
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
};
struct Point
{
	GLint x;
	GLint y;
};

void putPixel(GLint x, GLint y, Color color)
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

//enumerating menu items
enum MenuItems
{
	FLOOD_FILL,
	BOUNDARY_FILL,
	SCANLINE_FILL,
	RESET,
};

MenuItems show = FLOOD_FILL;

Color getPixelColor(GLint x, GLint y)
{
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}


void FloodFill(GLint x, GLint y, Color oldColor, Color newColor )
{
	Color color= getPixelColor(x, y);
	if (color.r==oldColor.r && color.g==oldColor.g && color.b==oldColor.b)
	{
		putPixel(x, y, newColor);
		FloodFill(x, y+1, oldColor, newColor);
		FloodFill(x+1, y, oldColor, newColor);
		FloodFill(x-1, y, oldColor, newColor);
		FloodFill(x, y-1, oldColor, newColor);
		FloodFill(x-1, y-1, oldColor, newColor);
		FloodFill(x+1, y-1, oldColor, newColor);
		FloodFill(x-1, y+1, oldColor, newColor);
	}
	return;
}

void boundaryFill(GLint x, GLint y, Color fillColor, Color boundaryColor)
{
	Color color = getPixelColor(x, y);
	/*cout << color.r << " " << boundaryColor.r << endl;
	cout << color.g << " " << boundaryColor.g << endl;
	cout << color.b << " " << boundaryColor.b << endl;*/
	if(color.r != boundaryColor.r || color.g != boundaryColor.g || color.b != boundaryColor.b)
	{
		if (color.r != fillColor.r || color.g != fillColor.g || color.b != fillColor.b)
		{
			
		putPixel(x, y, fillColor);
		boundaryFill(x-1, y, fillColor, boundaryColor);
		boundaryFill(x+1, y, fillColor, boundaryColor);
		boundaryFill(x, y+1, fillColor, boundaryColor);
		boundaryFill(x, y-1, fillColor, boundaryColor);
		}
	}
	
}

void mouse(int button, int state, int x, int y)
{
	Color newColor = {1.0f, 0.0f, 0.0f};
	Color oldColor = {0.0f, 0.0f, 0.0f};
	Color borderColor = {0.0f, 1.0f, 0.0f};
	//if (button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (floodFillFlag)
		{
			//cout <<x << y<<endl;
			FloodFill(x,(originalHeight - y), oldColor, newColor);
			floodFillFlag = false;
		}
		if (boundaryFillflag)
		{
			boundaryFill(x, (originalHeight -y), newColor, borderColor );
			boundaryFillflag = false;
		}
	}
}



//function to handle menu
static void menu (int item)
{
	switch(item)
	{
		case FLOOD_FILL:
		{
			floodFillFlag = true;
			break;
		}

		case BOUNDARY_FILL:
		{
			boundaryFillflag = true;
			break;
		}
	}
}



void drawFigure1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(250, 300 );
		glVertex2f(50, 160);
		glVertex2f(100, 59);
		glVertex2f(100, 160);
	glEnd();
	glFlush();
}

void drawFigure2()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	GLfloat radius = 75;
	GLfloat step = 1/radius;
	GLfloat x, y;
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
		GLfloat theta = 0;
		for(; theta <= 360; theta += step) {
		x = 325 + (radius * cos(theta));
		y = 400 + (radius * sin(theta));
		glVertex2i(x, y);
	}
	glEnd();
	glFlush();
}

void display()
{
	drawFigure1();
	drawFigure2();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(originalWidth, originalHeight);
	glutInitWindowPosition(100, 100);
	
	glutCreateWindow("Canvas");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutCreateMenu(menu);
		glutAddMenuEntry("Flood Fill", FLOOD_FILL);
		glutAddMenuEntry("Boundary Fill", BOUNDARY_FILL);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}