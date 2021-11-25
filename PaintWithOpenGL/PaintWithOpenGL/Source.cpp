// #include "stdafx.h"
#include <GL/glut.h>
#include <stdio.h>
#include<cmath>
#include <cstdlib>

int ww = 600, wh = 400;
int xi, yi, xf, yf, m;

void calCordinates(GLint x1, GLint y1, GLint x2, GLint y2) {

	int dx = x2 - x1;
	int dy = y2 - y1;

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;

	float X = x1;
	float Y = y1;

	for (int i = 0; i <= steps; i++)
	{
		glVertex2i(X, Y);
		X += Xinc;
		Y += Yinc;
	}

}

void drawLine(GLint x1, GLint y1, GLint x2, GLint y2)
{
	glPointSize(2.0);

	glBegin(GL_POINTS);
	calCordinates(x1, y1, x2, y2);
	glEnd();

	glFlush();
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)
		{
			xi = x;
			yi = (wh - y);
		}
		else if (state == GLUT_UP) {
			xf = x;
			yf = (wh - y);
		}

	if (xi != 0 && xf != 0)
		drawLine(xi, yi, xf, yf);

	if (btn == GLUT_RIGHT_BUTTON) {
		// glClear(GL_COLOR_BUFFER_BIT);
		// glFlush();
		xi = 0;
		xf = 0;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q') exit(0);

	else if (key == 'e' || key == 'E') 
{
		xi = 0;
		xf = 0;
		glClear(GL_COLOR_BUFFER_BIT);
		glutPostRedisplay();
		glFlush();
	}
}

void myinit()
{
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutCreateWindow("Simple Paint-like Program");
	myinit();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}