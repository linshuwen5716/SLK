#include "stdafx.h"
#include "glut.h"
#include <iostream>
#include <vector>
#include <ctime>

#include "glheader.h"
#include "versionheader.h"
#include "slkheader.h"
#include "Particle.h"

using namespace std;

vector<Particle *>* particles;

void glInit(int *, char **);
void display();
void idle();
void keyboardFunc(unsigned char key, int x, int y);

void particlesInit();

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));

	particlesInit();
	glInit(&argc, argv);

	return 0;
}

void glInit(int *argc, char **argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(VERSION_STRING);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);

	const GLubyte* name = glGetString(GL_VENDOR);
	const GLubyte* rendererVersion = glGetString(GL_RENDERER);
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION);
	const GLubyte* gluVersion = gluGetString(GLU_VERSION);

	cout << "Vendor: " << name << endl;
	cout << "Renderer: " << rendererVersion << endl;
	cout << "OpenGLVersion: " << OpenGLVersion << endl;
	cout << "gluVersion: " << gluVersion << endl;

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboardFunc);

	glutMainLoop();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(2);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);

	Point2D* pos;
	for (int i = 0; i < PARTICLE_COUNT; ++i) {
		pos = particles->at(i)->getParticlePos();
		glVertex2f(pos->x, pos->y);
	}
	glEnd();

	glutSwapBuffers();
	glFlush();
}

void idle()
{
	for (int i = 0; i < PARTICLE_COUNT; ++i) {
		particles->at(i)->updatePos(particles->at(i)->getF(particles, i));
	}

	glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':  //reset
	case 'R':
		//
		break;
	case 'p':  //pause
	case 'P':
		//
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void particlesInit() {
	particles = new vector<Particle *>();

	for (int i = 0; i < PARTICLE_COUNT; ++i) {
		particles->push_back(new Particle(1, 1, new Point2D(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT), new Point2D()));
	}
}

