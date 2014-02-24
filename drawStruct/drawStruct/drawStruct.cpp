#include <windows.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>



#define GL_PI 3.1415f

static GLfloat xRot = 0.f;
static GLfloat yRot = 0.f;

void SetupRC()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);

	glColor3f(0.f, 1.f,0.f);
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xRot, 1.f, 0.f, 0.f);
	glRotatef(yRot, 0.f, 1.f, 0.f);

	//원하는 shape를 선택하세요~!

	//glutWireTeapot(1.f);
	//glutWireSphere(1.f, 10, 5);
	//glutWireCone(1.f, 1.f, 8, 4);
	//glutWireTorus(.3f, 1.f, 5, 8);
	//glutWireTetrahedron();
	
	// glutWireCube(2.8f);

	glutSolidCube(2.8f);

	//glutWireDodecahedron();
	//glutWireIcosahedron();

	glPopMatrix();

	glutSwapBuffers();
}

void KeyControl(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot -= 5.f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.f;

	glutPostRedisplay();
}

void ChangeSize(GLint w, GLint h)
{
	GLfloat nRange = 2.f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	if(w<=h)
		glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);

	else
		glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(512,512);
	glutCreateWindow("Spring Vertex");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);

	SetupRC();
	glutMainLoop();
}