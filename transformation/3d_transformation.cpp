#include <GL/glut.h>
#include  <iostream>
#include <math.h>
using namespace std;

bool scaleFlag = false, rotationFlag = false, translateFlag = false, reflectionFlag = false;
double rotate_y=0; 
double rotate_x=0;
struct Point
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct Line
{
	Point start;
	Point end;
};

struct Cube
{
	Point a1 ;
	Point a2 ;
	Point a3 ;
	Point a4 ;
	Point a5 ;
	Point a6 ;
	Point a7 ;
	Point a8 ;
};

//
Point a1 = {-50, 50, -50};
Point a2 = {50, 50, -50};
Point a3 = {50, -50, -50};
Point a4 = {-50, -50, -50};
Point a5 = {50, -50, 50};
Point a6 = {-50, -50, 50};
Point a7 = {50, 50, 50};
Point a8 = {-50, 50, 50};

Cube originalCube = {a1, a2, a3, a4, a5, a6, a7, a8};

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

void drawCube(Cube inputCube)
{
	glBegin(GL_POLYGON); //front face
	glColor3f(0.0f,1.0f,0.0f);    // Color Green
		glVertex3f(inputCube.a1.x, inputCube.a1.y, inputCube.a1.z); //top front left
		glVertex3f(inputCube.a2.x, inputCube.a2.y, inputCube.a2.z); // top front right
		glVertex3f(inputCube.a3.x, inputCube.a3.y, inputCube.a3.z); // bottom front right
		glVertex3f(inputCube.a4.x, inputCube.a4.y, inputCube.a4.z); //bottom front left
	 glEnd();
	// glFlush();
	glBegin(GL_POLYGON); //bottom face
	glColor3f(1.0f,0.0f,0.0f);    // Color Red
		glVertex3f(inputCube.a4.x, inputCube.a4.y, inputCube.a4.z); //bottom frontleft
		glVertex3f(inputCube.a3.x, inputCube.a3.y, inputCube.a3.z); // bottom front right
		glVertex3f(inputCube.a5.x, inputCube.a5.y, inputCube.a5.z); //bottom back right 
		glVertex3f(inputCube.a6.x, inputCube.a6.y, inputCube.a6.z); // bottom back left
	glEnd();
	glBegin(GL_POLYGON); //back face
	glColor3f(0.0f,.0f,1.0f);    // Color Blue
		glVertex3f(inputCube.a6.x, inputCube.a6.y, inputCube.a6.z); // bottom back left
		glVertex3f(inputCube.a5.x, inputCube.a5.y, inputCube.a5.z); //bottom back right 
		glVertex3f(inputCube.a7.x, inputCube.a7.y, inputCube.a7.z); //top back right
		glVertex3f(inputCube.a8.x, inputCube.a8.y, inputCube.a8.z); // top back left
	glEnd();
	glBegin(GL_POLYGON); //top face
	glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(inputCube.a8.x, inputCube.a8.y, inputCube.a8.z); // top back left
		glVertex3f(inputCube.a7.x, inputCube.a7.y, inputCube.a7.z); //top back right
		glVertex3f(inputCube.a2.x, inputCube.a2.y, inputCube.a2.z); // top front right
		glVertex3f(inputCube.a1.x, inputCube.a1.y, inputCube.a1.z); //top front left
	glEnd();
	glBegin(GL_POLYGON); //left face
	glColor3f(.0f, 1.0f, 1.0f);
		glVertex3f(inputCube.a8.x, inputCube.a8.y, inputCube.a8.z); // top back left
		glVertex3f(inputCube.a1.x, inputCube.a1.y, inputCube.a1.z); //top front left
		glVertex3f(inputCube.a4.x, inputCube.a4.y, inputCube.a4.z); //bottom frontleft
		glVertex3f(inputCube.a6.x, inputCube.a6.y, inputCube.a6.z); // bottom back left
	glEnd();
	glBegin(GL_POLYGON); //right face
	glColor3f(1.0f, .0f, 1.0f);
		glVertex3f(inputCube.a2.x, inputCube.a2.y, inputCube.a2.z); // top front right
		glVertex3f(inputCube.a3.x, inputCube.a3.y, inputCube.a3.z); // bottom front right
		glVertex3f(inputCube.a5.x, inputCube.a5.y, inputCube.a5.z); //bottom back right 
		glVertex3f(inputCube.a7.x, inputCube.a7.y, inputCube.a7.z); //top back right
	glEnd();
	glFlush();
}

void displayOriginal()
{
	glRotatef( rotate_x, 1.0, 0.0, 0.0 );
	glRotatef( rotate_y, 0.0, 1.0, 0.0 );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0,0.0);
	drawCube(originalCube);
	glFlush();
	glutSwapBuffers();
}

Cube translate(Cube inputCube, GLint dx, GLint dy, GLint dz)
{
	cout << "original " << inputCube.a1.x << " " << inputCube.a1. y << " " << inputCube.a1.z << endl;
	Cube newCube = {{inputCube.a1.x + dx, inputCube.a1.y + dy,inputCube.a1.z + dz}, {inputCube.a2.x + dx, inputCube.a2.y + dy,inputCube.a2.z + dz}, {inputCube.a3.x + dx, inputCube.a3.y + dy,inputCube.a3.z + dz}, {inputCube.a4.x + dx, inputCube.a4.y + dy,inputCube.a4.z + dz}, {inputCube.a5.x + dx, inputCube.a5.y + dy,inputCube.a5.z + dz}, {inputCube.a6.x + dx, inputCube.a6.y + dy,inputCube.a6.z + dz}, {inputCube.a7.x + dx, inputCube.a7.y + dy,inputCube.a7.z + dz}, {inputCube.a8.x + dx, inputCube.a8.y + dy,inputCube.a8.z + dz}, };
	cout << "new " << newCube.a1.x << " " << newCube.a1.y << " " << newCube.a1.z << endl;
	cout << "new " << newCube.a2.x << " " << newCube.a2.y << " " << newCube.a2.z << endl;
	cout << "new " << newCube.a3.x << " " << newCube.a3.y << " " << newCube.a3.z << endl;
	cout << "new " << newCube.a4.x << " " << newCube.a4.y << " " << newCube.a4.z << endl;
	return newCube;
}

Cube rotate(Cube inputCube, GLfloat angle)
{

	//Taking the figure to
	GLfloat newVertexVectorA1[3], newVertexVectorA2[3], newVertexVectorA3[3], newVertexVectorA4[3], newVertexVectorA5[3], newVertexVectorA6[3], newVertexVectorA7[3], newVertexVectorA8[3];
	
	GLfloat oldVertexVectorA1[3] = {inputCube.a1.x, inputCube.a1.y, inputCube.a1.z};
	GLfloat oldVertexVectorA2[3] = {inputCube.a2.x, inputCube.a2.y, inputCube.a2.z};
	GLfloat oldVertexVectorA3[3] = {inputCube.a3.x, inputCube.a3.y, inputCube.a3.z};
	GLfloat oldVertexVectorA4[3] = {inputCube.a4.x, inputCube.a4.y, inputCube.a4.z};
	GLfloat oldVertexVectorA5[3] = {inputCube.a5.x, inputCube.a5.y, inputCube.a5.z};
	GLfloat oldVertexVectorA6[3] = {inputCube.a6.x, inputCube.a6.y, inputCube.a6.z};
	GLfloat oldVertexVectorA7[3] = {inputCube.a7.x, inputCube.a7.y, inputCube.a7.z};
	GLfloat oldVertexVectorA8[3] = {inputCube.a8.x, inputCube.a8.y, inputCube.a8.z};

	cout << cos(angle) << " " << sin(angle) <<endl;

	GLfloat rotationMatrix[3][3] = {{cos(angle), sin(angle), 0}, {sin(angle), -cos(angle), 0}, {0,0,1}};
	
	matrixMultiplication(oldVertexVectorA4, rotationMatrix, newVertexVectorA4);
	matrixMultiplication(oldVertexVectorA3, rotationMatrix, newVertexVectorA3);
	matrixMultiplication(oldVertexVectorA2, rotationMatrix, newVertexVectorA2);
	matrixMultiplication(oldVertexVectorA1, rotationMatrix, newVertexVectorA1);
	matrixMultiplication(oldVertexVectorA5, rotationMatrix, newVertexVectorA5);
	matrixMultiplication(oldVertexVectorA6, rotationMatrix, newVertexVectorA6);
	matrixMultiplication(oldVertexVectorA7, rotationMatrix, newVertexVectorA7);
	matrixMultiplication(oldVertexVectorA8, rotationMatrix, newVertexVectorA8);
	
	Point newA4 = {newVertexVectorA4[0], newVertexVectorA4[1],newVertexVectorA4[2]};
	Point newA3 = {newVertexVectorA3[0], newVertexVectorA3[1],newVertexVectorA3[2]};
	Point newA2 = {newVertexVectorA2[0], newVertexVectorA2[1],newVertexVectorA2[2]};
	Point newA1 = {newVertexVectorA1[0], newVertexVectorA1[1],newVertexVectorA1[2]};
	Point newA5 = {newVertexVectorA5[0], newVertexVectorA5[1],newVertexVectorA5[2]};
	Point newA6 = {newVertexVectorA6[0], newVertexVectorA6[1],newVertexVectorA6[2]};
	Point newA7 = {newVertexVectorA7[0], newVertexVectorA7[1],newVertexVectorA7[2]};
	Point newA8 = {newVertexVectorA8[0], newVertexVectorA8[1],newVertexVectorA8[2]};

	Cube rotatedCube = {newA1, newA2, newA3, newA4, newA5, newA6, newA7, newA8};
	return rotatedCube;	
}

Cube reflection(Cube inputCube, Line referneceLine)
{
	GLfloat slope = atan((referneceLine.start.y - referneceLine.end.y)/(referneceLine.start.x - referneceLine.end.x));
	Cube shiftedCube = rotate(inputCube, -slope);
	Cube intermediateCube = shiftedCube;
	//drawTriangle(intermediateTriangle);
	Cube finalCube = rotate(intermediateCube, slope);
	return finalCube;
}
void onMouseClick(int state, int button, int x, int y)
{
	if(translateFlag)
	{
		GLint dx = 100, dy = 100, dz = -150;
		drawCube(translate(originalCube, dx, dy, dz));
		translateFlag = false;
	}
	if(rotationFlag)
	{
		GLfloat angle = 3.14f/4.0f;
		drawCube(rotate(originalCube, angle));
		rotationFlag = false;
	}
	if(reflectionFlag)
	{
		Line l = {{0, 1}, {13,13}};
		drawCube(reflection(originalCube, l));
		reflectionFlag = false;	
	}

}

void specialKeys( int key, int x, int y )
{
 
  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT)
    {rotate_y += 3;
    	cout << "Right key pressed"<< endl;}
 
  //  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 3;
 
  else if (key == GLUT_KEY_UP)
    rotate_x += 3;
 
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 3;
 
  //  Request display update
  glutPostRedisplay();
}

void init()
{
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -250, 250);

}

void menu(int item)
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
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Transformation");
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	init();
	glutMouseFunc(onMouseClick);
	glutCreateMenu(menu);
		glutAddMenuEntry("Translate", TRANSLATE);
		glutAddMenuEntry("Rotate", ROTATION);
		glutAddMenuEntry("Reflection", REFLECTION);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(displayOriginal);
	glutSpecialFunc(specialKeys);
	//glutIdleFunc(animation);
	glutMainLoop();
	return 0;
}