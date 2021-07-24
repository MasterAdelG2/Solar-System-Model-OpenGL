#include <cmath>
#include <algorithm>
#include <bits/stdc++.h>
#include <gl/glut.h>
#include "math.h"
#include "time.h"
#define GL_PI 3.1415f
#define X 0
#define Y 1
#define Z 2
int obkect = 1;
static GLfloat width;
static GLfloat height;
static GLfloat xRot1 = 0.0f;
static GLfloat yRot1 = 0.0f;
static GLfloat zRot1 = 0.0f;
static GLfloat Trans1[3] = { 0,0,0 };
static GLfloat angle1 = 0.0f;
static GLfloat xRot2 = 0.0f;
static GLfloat yRot2 = 0.0f;
static GLfloat zRot2 = 0.0f;
static GLfloat Trans2[3] = { 0,0,0 };
static GLfloat angle2 = 0.0f;
static GLfloat xRot3 = 0.0f;
static GLfloat yRot3 = 0.0f;
static GLfloat zRot3 = 0.0f;
static GLfloat Trans3[3] = { 0,0,0 };
static GLfloat angle3 = 0.0f;

static GLfloat xRotCam = 0.0f;
static GLfloat yRotCam = 0.0f;
static GLfloat Pos[3] = { -70.0,20.0,0.0 };
static GLfloat Center[3] = { 1,0,0 };
static GLfloat Up[3] = { 0,1,0 };
static bool bOutline = true;
static bool grid = true;
void DrawGround()
{
	GLfloat fExtent = 800.0f;
	GLfloat fStep = 8.0f;
	GLfloat y = -0.4f;
	GLint iLine;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (iLine = -fExtent; iLine <= fExtent; iLine += fStep)
	{
		glVertex3f(iLine, y, fExtent); // Draw Z lines
		glVertex3f(iLine, y, -fExtent);
		glVertex3f(fExtent, y, iLine);
		glVertex3f(-fExtent, y, iLine);
	}
	glEnd();
}
void DrawBall1()
{
	glPushMatrix();
	glTranslatef(Trans1[0], Trans1[1], Trans1[2]);
	glRotatef(xRot1, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot1, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot1, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(40, 20, 20);
	glPopMatrix();
}
void DrawBall2()
{
	glPushMatrix();
	GLfloat r = 230.0f;
	Trans2[0] = r*sin(angle2);
	Trans2[1] = 0;
	Trans2[2] = r*cos(angle2);
	// Update Transformation Matrix
	glTranslatef(Trans2[0], Trans2[1], Trans2[2]);
	glRotatef(xRot2, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot2, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot2, 0.0f, 0.0f, 1.0f);
	// Draw
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(20, 20, 20);
	glPopMatrix();
}
void DrawBall3()
{
	glPushMatrix();
	GLfloat r = 40.0f;
	Trans3[0] = Trans2[0] + r*sin(angle3);
	Trans3[1] = 0;
	Trans3[2] = Trans2[2] + r*cos(angle3);
	// Update Transformation Matrix
	glTranslatef(Trans3[0], Trans3[1], Trans3[2]);
	glRotatef(xRot3, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot3, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot3, 0.0f, 0.0f, 1.0f);
	// Draw
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(8, 8, 8);
	glPopMatrix();
}
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (bOutline)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluLookAt(Pos[X], Pos[Y], Pos[Z], Pos[X] + Center[X], Pos[Y] + Center[Y], Pos[Z] + Center[Z], Up[X], Up[Y], Up[Z]);
	if (grid)
		DrawGround();
	DrawBall1();
	DrawBall2();
	DrawBall3();
	glutSwapBuffers();
}
void SetupRC(void) {
	glClearColor(0.0f, 0.0f, 0.03f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}
void TimerFunction(int value)
{
	// Orbit speed
	angle2 += 0.03f;
	angle3 += 0.1f;
	// Rotation Speed
	zRot1 = int(zRot1 - 20.0) % 360;
	zRot2 = int(zRot2 + 30.0) % 360;
	zRot3 = int(zRot3 - 35.0) % 360;
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void ChangeSize(int w, int h) {
	GLfloat nRange = 800.0f;
	if (h == 0)	h = 1;
	width = w;
	height = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		gluPerspective(100.0, w / h, 0.5, nRange * 10);
	else
		gluPerspective(100.0, w / h, 0.5, nRange * 10);
	glMatrixMode(GL_MODELVIEW);
}
void Keys(unsigned char key, int x, int y)
{
	if (key == 'w') Pos[X] += Center[X], Pos[Y] += Center[Y], Pos[Z] += Center[Z];
	if (key == 's') Pos[X] -= Center[X], Pos[Y] -= Center[Y], Pos[Z] -= Center[Z];
	if (key == 'e') Pos[Y] += 1.0f;
	if (key == 'q') Pos[Y] -= 1.0f;
}
void SpecialKeys(int key, int x, int y)
{
	// Rotate
	if (key == GLUT_KEY_UP) yRotCam += 0.1;
	if (key == GLUT_KEY_DOWN) yRotCam -= 0.1;
	if (key == GLUT_KEY_LEFT) xRotCam -= 0.1;
	if (key == GLUT_KEY_RIGHT) xRotCam += 0.1;
	
	if (xRotCam >= 360.0) xRotCam = 0.1;
	if (xRotCam < 0.0) xRotCam = 359.9;
	if (yRotCam >= 360.0) yRotCam = 0.1;
	if (yRotCam < 0.0) yRotCam = 359.9;

	Center[X] = cos(xRotCam) * abs(cos(yRotCam));
	Center[Y] = sin(yRotCam);
	Center[Z] = sin(xRotCam) * abs(cos(yRotCam));
	// Up
	float tmp;
	if (cos(yRotCam) > 0)
		Up[Y] = 1, tmp = 1;
	else if (cos(yRotCam) <= 0)
		Up[Y] = -1, tmp = -1;
	Center[X] *= tmp;
	Center[Z] *= tmp;
	glutPostRedisplay();
}
void selectedPart(int v)
{
	switch (v)
	{
	case 1:
		bOutline = !bOutline;
		break;
	case 2:
		grid = !grid;
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 650);
	glutCreateWindow("perspectives");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(50, TimerFunction, 1);
	SetupRC();
	glutCreateMenu(selectedPart);
	glutKeyboardFunc(Keys);
	glutSpecialFunc(SpecialKeys);
	glutAddMenuEntry("Toggle Outlines", 1);
	glutAddMenuEntry("Toggle Grid", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}