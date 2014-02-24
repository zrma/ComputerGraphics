#include <stdlib.h>
#include <gl/glut.h>
#include <windows.h>
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC()
{
	GLfloat		ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat		diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f }; // ADD
	GLfloat		lightPos[] = { 150.f, -100.0f, -100.0f, 1.0f };

	glEnable(GL_DEPTH_TEST);	
	glFrontFace(GL_CCW);	
	glEnable(GL_CULL_FACE);	
	glEnable(GL_LIGHTING); 	
	// Setup and enable light 0

	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight); //ADD
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight); //ADD 
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	
	glEnable(GL_LIGHT0);                          //ADD
	glEnable(GL_COLOR_MATERIAL); 	
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	glViewport(0,0,w,h);
	fAspect = (GLfloat)w/(GLfloat)h; 
	glMatrixMode(GL_PROJECTION);

	
	glLoadIdentity();

	gluPerspective(45.0f,fAspect,1.0f,255.0f); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -150.0f);
}

void RenderScene(void)

{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// Nose Cone /////////////////////////////
	// Bright Green
	glColor3ub(0, 255, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 60.0f);
	glVertex3f(-15.0f, 0.0f, 30.0f);
	glVertex3f(15.0f,0.0f,30.0f);
	glVertex3f(15.0f,0.0f,30.0f);
	glVertex3f(0.0f, 15.0f, 30.0f);
	glVertex3f(0.0f, 0.0f, 60.0f);
	glVertex3f(0.0f, 0.0f, 60.0f);
	glVertex3f(0.0f, 15.0f, 30.0f);
	glVertex3f(-15.0f,0.0f,30.0f);

	// Body of the Plane ////////////////////////
	// light gray
	glColor3ub(192,192,192);
	glVertex3f(-15.0f,0.0f,30.0f);
	glVertex3f(0.0f, 15.0f, 30.0f);
	glVertex3f(0.0f, 0.0f, -56.0f);
	glVertex3f(0.0f, 0.0f, -56.0f);
	glVertex3f(0.0f, 15.0f, 30.0f);
	glVertex3f(15.0f,0.0f,30.0f);	
	glVertex3f(15.0f,0.0f,30.0f);
	glVertex3f(-15.0f, 0.0f, 30.0f);
	glVertex3f(0.0f, 0.0f, -56.0f);

	///////////////////////////////////////////////
	// Left wing
	// Dark gray
	glColor3ub(64,64,64);
	glVertex3f(0.0f,2.0f,27.0f);
	glVertex3f(-60.0f, 2.0f, -8.0f);
	glVertex3f(60.0f, 2.0f, -8.0f);
	glVertex3f(60.0f, 2.0f, -8.0f);
	glVertex3f(0.0f, 7.0f, -8.0f);
	glVertex3f(0.0f,2.0f,27.0f);
	glVertex3f(60.0f, 2.0f, -8.0f);
	glVertex3f(-60.0f, 2.0f, -8.0f);
	glVertex3f(0.0f,7.0f,-8.0f);

	// Other wing top section
	glVertex3f(0.0f,2.0f,27.0f);
	glVertex3f(0.0f, 7.0f, -8.0f);
	glVertex3f(-60.0f, 2.0f, -8.0f);

	// Tail section///////////////////////////////
	// Bottom of back fin
	glColor3ub(255,255,0);
	glVertex3f(-30.0f, -0.50f, -57.0f);
	glVertex3f(30.0f, -0.50f, -57.0f);
	glVertex3f(0.0f,-0.50f,-40.0f);

	// top of left side
	glVertex3f(0.0f,-0.5f,-40.0f);
	glVertex3f(30.0f, -0.5f, -57.0f);
	glVertex3f(0.0f, 4.0f, -57.0f);

	// top of right side
	glVertex3f(0.0f, 4.0f, -57.0f);
	glVertex3f(-30.0f, -0.5f, -57.0f);
	glVertex3f(0.0f,-0.5f,-40.0f);

	// back of bottom of tail
	glVertex3f(30.0f,-0.5f,-57.0f);
	glVertex3f(-30.0f, -0.5f, -57.0f);
	glVertex3f(0.0f, 4.0f, -57.0f);

	// Top of Tail section left
	glColor3ub(255,0,0);
	glVertex3f(0.0f,0.5f,-40.0f);
	glVertex3f(3.0f, 0.5f, -57.0f);
	glVertex3f(0.0f, 25.0f, -65.0f);

	glVertex3f(0.0f, 25.0f, -65.0f);
	glVertex3f(-3.0f, 0.5f, -57.0f);
	glVertex3f(0.0f,0.5f,-40.0f);

	// Back of horizontal section
	glVertex3f(3.0f,0.5f,-57.0f);
	glVertex3f(-3.0f, 0.5f, -57.0f);
	glVertex3f(0.0f, 25.0f, -65.0f);
	glEnd();

	glPopMatrix();

	// Display the results
	glutSwapBuffers();
}

void KeyControl(int key, int x, int y) // 윈도우 상의 좌표와 key값이 입력됨
{
	if(key == GLUT_KEY_UP)
		xRot -=5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot +=5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -=5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot +=5.0f;

	glutPostRedisplay();               // 변환된 좌표값으로 redrawing

}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512,512);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Light Jet");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}
