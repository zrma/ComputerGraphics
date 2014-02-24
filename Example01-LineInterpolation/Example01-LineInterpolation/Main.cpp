#include <stdlib.h>
#include <gl/glut.h>
#include <windows.h>
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	// glEnable(GL_DEPTH_TEST);	//add
	// glFrontFace(GL_CCW);		//add
	glFrontFace(GL_CW);			//add
	glEnable(GL_CULL_FACE);		//add	 
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}


void ChangeSize(int w, int h)
{
	GLfloat nRange = 300.0f;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f, nRange*2.0f);	//add
	else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);	//add

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/*
void ChangeSize(int w, int h)
{

	GLfloat fAspect;

	glViewport(0,0,w,h);

	fAspect = (GLfloat)w/(GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, fAspect, 1.0f, 700.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
*/

void RenderScene() // add – draw 3 sphere 
{	
	glClear(GL_COLOR_BUFFER_BIT);
	// Enable smooth shading
	
	glMatrixMode(GL_MODELVIEW);         // 모델뷰 행렬 초기화
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -100.0f);

	glShadeModel(GL_SMOOTH);

	glBegin(GL_TRIANGLES);
	// Red Apex
	glColor3ub((GLubyte)255,(GLubyte)0,(GLubyte)0);
	glVertex3f(0.0f,200.0f,0.0f);

	// Green on the right bottom corner
	glColor3ub((GLubyte)0,(GLubyte)255,(GLubyte)0);
	glVertex3f(200.0f,-70.0f,0.0f);

	// Blue on the left bottom corner
	glColor3ub((GLubyte)0,(GLubyte)0,(GLubyte)255);
	glVertex3f(-200.0f, -70.0f, 0.0f);
	glEnd();

	glPopMatrix();

	// Flush drawing commands
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
	glutCreateWindow("LineInterpolation");

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33,TimerFunc,1); //add 
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}
