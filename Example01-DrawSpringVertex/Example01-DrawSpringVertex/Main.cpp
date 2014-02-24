#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f); 

	glColor3f(0.0f,1.0f,0.0f);

} 
void RenderScene(void)
{
	GLfloat x, y, z, angle;
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	// 변환 연산을 하기 위한 매트릭스 받아 옴

	glRotatef( xRot , 1.0f , 0.0f , 0.0f ); // x축 회전
	glRotatef( yRot , 0.0f , 1.0f , 0.0f ); // y축 회전

	//////////////////////////////////////////////////////////////////////////
	// glBegin(GL_POINTS);
	glBegin(GL_TRIANGLE_STRIP);
	// Begin
	//////////////////////////////////////////////////////////////////////////

	z = -50.0f;

	for(angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle +=0.1f)  
		// 3.14/0.1 개의 포인트를 뿌린다 총 3바퀴 
	{
		x = 60.0f * sin(angle);
		y = 60.0f * cos(angle);
		glVertex3f(x,y,z);
		z += 0.5f;
	}

	//////////////////////////////////////////////////////////////////////////
	glEnd();
	// End
	//////////////////////////////////////////////////////////////////////////

	glPopMatrix();
	glutSwapBuffers();
}

void KeyControl(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot -=5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot +=5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -=5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot +=5.0f;

	glutPostRedisplay();

}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glViewport( 0 , 0 , w , h );

	if(w<=h)
		glOrtho( -nRange , nRange , -nRange * h / w , nRange * h / w , -nRange , nRange );
	else
		glOrtho( -nRange * w / h , nRange * w / h , -nRange , nRange , -nRange , nRange );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

void main(void)
{
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	// GLUT_DOUBLE : Frame Buffer - Double 버퍼 사용
	// GLUT_DEPTH : Z-Buffer 이용

	glutInitWindowPosition(0,0); // add
	glutInitWindowSize(512,512); // add
	glutCreateWindow("SpringVertex");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl); // add
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

}