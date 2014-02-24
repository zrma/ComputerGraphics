#include <stdlib.h>
#include <gl/glut.h>
#include <windows.h>
#include <math.h>

#define GL_PI 3.1415f

GLfloat  lightPos[] = {0.0f, 0.0f, 50.0f, 1.0f};

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC()
{
	GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat	 specular[] = { 0.5f, 0.3f, 0.3f, 1.0f };

	glEnable(GL_DEPTH_TEST);		// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	glEnable(GL_LIGHTING); 		// Enable lighting
	// Setup and enable light 0
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	// glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMateriali(GL_FRONT, GL_SHININESS, 80);

	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL); 	// Enable color tracking
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

	gluPerspective(60.0f,fAspect,1.0f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f,0.0f, -200.0f); //add 
}						

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();	
	glRotatef(yRot, 0.0f, 1.0f, 0.0f); // Rotate coordinate system
	glRotatef(xRot, 1.0f, 0.0f, 0.0f); // Rotate coordinate system

	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  // 변환 안에 Light의 position을 입력하면 변환행렬 적용됨
	glTranslatef(lightPos[0],lightPos[1],lightPos[2]);
	glColor3ub(255,0,0);	
	glutSolidCone(4.0f,6.0f,15,15);

	glColor3ub(255,255,0);
	glutSolidSphere(3.0f, 15, 15);

	glPopMatrix();
	glColor3ub(0, 255, 255);
	
	glPushMatrix();
	glRotatef(45.f, 0.f, 1.f, 0.f);
	// glFrontFace(GL_CW);
	glutSolidCube(30);
	// glFrontFace(GL_CCW);
	glPopMatrix();

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
	glutCreateWindow("Corn Light");

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33,TimerFunc,1); //add 
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}
