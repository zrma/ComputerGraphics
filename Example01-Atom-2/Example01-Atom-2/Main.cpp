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
{	
	static float shoulder = 0.0f;
	static float elbow = 0.0f;

	glClear (GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -7.0);

	// Push (1번스택에 현재 관측 지점 저장)
	glPushMatrix(); 
	glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);

	//1만큼 이동(왼쪽끝 모서리가중점이되어돌아가도록설정)
	glTranslatef (1.0, 0.0, 0.0); 

	//Push (스택에어깨라인큐브의변환행렬저장)
	glPushMatrix();        

	//scaling 한뒤 어깨큐브를 그림
	glScalef (2.0, 0.4, 1.0);
	glutWireCube (1.0);    //// GL_LINE 명령어로대체가능

	// POP( 어깨라인큐브의변환행렬을꺼내서복구)
	// Scaling 변환 delete
	glPopMatrix(); 

	// x축방향으로1만큼이동(숄더와겹치지않도록)
	glTranslatef (1.0, 0.0, 0.0); 

	// 팔뚝부분회전변환형렬
	glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0); 

	//1만큼 이동
	//(왼쪽끝모서리가중점이되어돌아가도록설정)
	glTranslatef (1.0, 0.0, 0.0);
	glScalef (2.0, 0.4, 1.0);
	glutWireCube (1.0);

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
	glutCreateWindow("Atom");

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33,TimerFunc,1); //add 
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}
