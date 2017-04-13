#include <GL/glut.h>
#include  <iostream>
#include <math.h>
using namespace std;

bool scaleFlag = false, rotationFlag = false, translateFlag = false, reflectionFlag = false;

struct Point
{
	GLint x;
	GLint y;
	GLint z;
};

struct Line
{
	Point start;
	Point end;
};

struct Triangle
{
	Point a1 ;
	Point a2 ;
	Point a3 ;
	//Point a4 ;
};

Point a1 = {15, 25, 0};
Point a2 = {115, 125, 0};
Point a3 = {215, 25, 0};
Triangle originalTriangle = {a1, a2, a3};

enum MenuItems
{
	TRANSLATE,
	ROTATION,
	REFLECTION,
	SCALE,
};

MenuItems show = TRANSLATE;


void matrixMultiplication(GLfloat a[3], GLfloat b[3][3], GLfloat prod[3])
{
	prod[0] = a[0]*b[0][0] + a[1]*b[1][0] + a[2]*b[2][0];
	prod[1] = a[0]*b[0][1] + a[1]*b[1][1] + a[2]*b[2][1];
	prod[2] = a[0]*b[0][2] + a[1]*b[1][2] + a[2]*b[2][2];
}

void drawTriangle(Triangle originalTriangle)
{
	glBegin(GL_LINE_STRIP);
		glVertex2f(originalTriangle.a1.x, originalTriangle.a1.y);
		glVertex2f(originalTriangle.a2.x, originalTriangle.a2.y);
		glVertex2f(originalTriangle.a3.x, originalTriangle.a3.y);
		glVertex2f(originalTriangle.a1.x, originalTriangle.a1.y);
	glEnd();
	glFlush();
}



Triangle translate(Triangle inputTriangle, GLint dx, GLint dy)
{
	GLfloat newVertexVectorA1[3], newVertexVectorA2[3], newVertexVectorA3[3], newVertexVectorA4[3];
	
	GLfloat oldVertexVectorA1[3] = {inputTriangle.a1.x, inputTriangle.a1.y, 1};
	GLfloat oldVertexVectorA2[3] = {inputTriangle.a2.x, inputTriangle.a2.y, 1};
	GLfloat oldVertexVectorA3[3] = {inputTriangle.a3.x, inputTriangle.a3.y, 1};
	//GLfloat oldVertexVectorA4[3] = {inputTriangle.a4.x, inputTriangle.a4.y, 1};
	
	GLfloat translationMatrix[3][3] = {{1,0,0}, {0,1,0}, {dx, dy, 1}};
	//matrixMultiplication(oldVertexVectorA4, translationMatrix, newVertexVectorA4);
	matrixMultiplication(oldVertexVectorA3, translationMatrix, newVertexVectorA3);
	matrixMultiplication(oldVertexVectorA2, translationMatrix, newVertexVectorA2);
	matrixMultiplication(oldVertexVectorA1, translationMatrix, newVertexVectorA1);

	//Point newA4 = {newVertexVectorA4[0], newVertexVectorA4[1], 1};
	Point newA3 = {newVertexVectorA3[0], newVertexVectorA3[1], 1};
	Point newA2 = {newVertexVectorA2[0], newVertexVectorA2[1], 1};
	Point newA1 = {newVertexVectorA1[0], newVertexVectorA1[1], 1};

	Triangle newTriangle = {newA1, newA2, newA3};
	return newTriangle;
}

Triangle rotate(Triangle inputTriangle, GLfloat angle)
{

	//Taking the figure to origin
	int x = -75; int y=0;
	Triangle triangleAtOrigin = translate(inputTriangle, x, y);
	
	GLfloat newVertexVectorA1[3], newVertexVectorA2[3], newVertexVectorA3[3], newVertexVectorA4[3];
	
	GLfloat oldVertexVectorA1[3] = {triangleAtOrigin.a1.x, triangleAtOrigin.a1.y, 1};
	GLfloat oldVertexVectorA2[3] = {triangleAtOrigin.a2.x, triangleAtOrigin.a2.y, 1};
	GLfloat oldVertexVectorA3[3] = {triangleAtOrigin.a3.x, triangleAtOrigin.a3.y, 1};
	//GLfloat oldVertexVectorA4[3] = {triangleAtOrigin.a4.x, triangleAtOrigin.a4.y, 1};

	cout << cos(angle) << " " << sin(angle) <<endl;

	GLfloat rotationMatrix[3][3] = {{cos(angle), sin(angle), 0}, {sin(angle), -cos(angle), 0}, {0,0,1}};
	
	//matrixMultiplication(oldVertexVectorA4, rotationMatrix, newVertexVectorA4);
	matrixMultiplication(oldVertexVectorA3, rotationMatrix, newVertexVectorA3);
	matrixMultiplication(oldVertexVectorA2, rotationMatrix, newVertexVectorA2);
	matrixMultiplication(oldVertexVectorA1, rotationMatrix, newVertexVectorA1);
	
	//Point newA4 = {newVertexVectorA4[0], newVertexVectorA4[1], 1};
	Point newA3 = {newVertexVectorA3[0], newVertexVectorA3[1], 1};
	Point newA2 = {newVertexVectorA2[0], newVertexVectorA2[1], 1};
	Point newA1 = {newVertexVectorA1[0], newVertexVectorA1[1], 1};

	Triangle rotatedTriangle = {newA1, newA2, newA3};

	Triangle finalTriangle = translate(rotatedTriangle, -x, y);
	// cout << "New Cordinates "<<newTriangle.a1.x << " " << newTriangle.a4.y <<endl;
	return finalTriangle;	
}

Triangle reflection(Triangle inputTriangle, Line referneceLine)
{
	GLfloat slope = atan((referneceLine.start.y - referneceLine.end.y)/(referneceLine.start.x - referneceLine.end.x));
	Triangle shiftedTriangle = rotate(inputTriangle, -slope);
	//drawTriangle(shiftedTriangle);
	Point newA1, newA2, newA3;
	newA1.x = shiftedTriangle.a1.x;
	newA3.x = shiftedTriangle.a3.x;
	newA2.x = shiftedTriangle.a2.x;
	
	newA1.y = -shiftedTriangle.a1.y;
	newA3.y = -shiftedTriangle.a3.y;
	newA2.y = -shiftedTriangle.a2.y;

	Triangle intermediateTriangle = {newA1, newA2, newA3};
	//drawTriangle(intermediateTriangle);
	Triangle finalTriangle = rotate(intermediateTriangle, slope);
	return finalTriangle;
}

Triangle scaling(Triangle inputTriangle, GLfloat sX, GLfloat sY)
{
	GLint x = -40, y=-30;
	Triangle shiftedTirangle = translate(inputTriangle, x, y);
	//drawTriangle(shiftedTirangle);
	GLfloat newVertexVectorA1[3], newVertexVectorA2[3], newVertexVectorA3[3];

	GLfloat oldVertexVectorA1[3] = {shiftedTirangle.a1.x, shiftedTirangle.a1.y, 1};
	GLfloat oldVertexVectorA2[3] = {shiftedTirangle.a2.x, shiftedTirangle.a2.y, 1};
	GLfloat oldVertexVectorA3[3] = {shiftedTirangle.a3.x, shiftedTirangle.a3.y, 1};
	
	GLfloat scalingMatrix[3][3] = {{sX, 0, 0}, {0,sY, 0}, {0, 0, 1}};

	matrixMultiplication(oldVertexVectorA3, scalingMatrix, newVertexVectorA3);
	matrixMultiplication(oldVertexVectorA2, scalingMatrix, newVertexVectorA2);
	matrixMultiplication(oldVertexVectorA1, scalingMatrix, newVertexVectorA1);

	Point newA3 = {newVertexVectorA3[0], newVertexVectorA3[1], 1};
	Point newA2 = {newVertexVectorA2[0], newVertexVectorA2[1], 1};
	Point newA1 = {newVertexVectorA1[0], newVertexVectorA1[1], 1};

	Triangle scaledTriangle = {newA1, newA2, newA3};

	Triangle finalTriangle = translate(scaledTriangle, -x, -y);
	return finalTriangle;
}



void displayOriginal()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0,0.0);
	drawTriangle(originalTriangle);
	glFlush();
}

void onMouseClick(int a, int b, int c, int d)
{
	if(translateFlag)
	{

		int x =-200; int y = -40;
		Triangle translatedTriangle = translate(originalTriangle, x, y);
		drawTriangle(translatedTriangle);
		translateFlag = false;
	}
	if(reflectionFlag)
	{
		Line l = {{0, 0}, {1,1}};
		Triangle reflectedTriangle = reflection(originalTriangle, l);
		drawTriangle(reflectedTriangle);
		reflectionFlag = false;	
	}
	if(rotationFlag)
	{
		GLfloat PI_4 = 3.14/4;
		Triangle rotatedTriangle = rotate(originalTriangle, PI_4 );
		drawTriangle(rotatedTriangle);
		rotationFlag = false;
	}
	if(scaleFlag)
	{
		Triangle scaledTriangle = scaling(originalTriangle, 1.5,1.5);
		drawTriangle(scaledTriangle);
		scaleFlag = false;
	}

}

static void menu (int item)
{
	switch(item)
	{
		case TRANSLATE:
		{
			translateFlag = true;
			break;
		}

		case REFLECTION:
		{
			reflectionFlag = true;
			break;
		}

		case ROTATION:
		{
			rotationFlag = true;
			break;
		}
		case SCALE:
		{
			scaleFlag = true;
			break;
		}
	}
	glutPostRedisplay();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Transformation");
	init();
	glutMouseFunc(onMouseClick);
	glutCreateMenu(menu);
		glutAddMenuEntry("Translate", TRANSLATE);
		glutAddMenuEntry("Rotate", ROTATION);
		glutAddMenuEntry("Reflection", REFLECTION);
		glutAddMenuEntry("Scale", SCALE);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(displayOriginal);
	glutMainLoop();
	return 0;
}