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
	glEnable(GL_DEPTH_TEST);  //add
	glFrontFace(GL_CCW);      //add
	glEnable(GL_CULL_FACE);   //add	 
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

/*
void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f, nRange*2.0f);               //add
	else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);  //add

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
*/

void ChangeSize(int w, int h)
{

	GLfloat fAspect;

	glViewport(0,0,w,h);

	fAspect = (GLfloat)w/(GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, fAspect, 1.0f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void RenderScene() // add – draw 3 sphere 
{	static GLfloat fElect1 = 0.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -100.0f);

	glRotatef(xRot,1.0f,0.0f,0.0f); 
	glRotatef(yRot,0.0f,1.0f,0.0f);

	glColor3ub(255, 0,0);
	// glutSolidSphere(10.0f,15,15);
	glutSolidCube(30.0f);


	//////////////////////////////////////////////////////////////////////////
	// 우측 위성
	glPushMatrix();		

	glRotatef(fElect1, 0.0f,1.0f,0.0f);
	glTranslatef(90.0f,0.0f,0.0f);

	glColor3ub(255,255,0);
	glutSolidSphere(6.0f,15,15);         
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	glPushMatrix();

	glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(fElect1, 0.0f,1.0f,0.0f); 
	glTranslatef(45.0f,0.0f,0.0f);

	glColor3ub(255,255,0);
	glutSolidSphere(6.0f,15,15);        
	
	glPopMatrix();	
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// 좌 하단 위성
	glPushMatrix();	

	glRotatef(45.0f, 0.0f,0.0f, 1.0f);
	glRotatef(fElect1, 0.0f,1.0f,0.0f);
	glTranslatef(-70.0f, 0.0f,0.0f);

	glutSolidSphere(6.0f,15,15);
	glPopMatrix();		
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// 맨 위 위성
	glPushMatrix();

	glRotatef(90.0f,0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 70.0f);

	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////

	fElect1 += 10.0f;	
	if(fElect1 > 360.0f)
		fElect1 = 0.0f;

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
	glutCreateWindow("Atom");

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33,TimerFunc,1); //add 
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}
