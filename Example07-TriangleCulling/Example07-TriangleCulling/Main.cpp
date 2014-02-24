#include <stdlib.h>
#include <gl/glut.h>
#include <windows.h>
#include <math.h>

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

bool iCull = FALSE;
bool iOutline = FALSE;
bool iDepth = FALSE;

void ProcessMenu(int value) // add
{
	switch(value)
	{
	case 1:
		iDepth = !iDepth;
		break;
	case 2:
		iCull = !iCull;
		break;
	case 3:
		iOutline = !iOutline;
		break;
	default :
		break;
	}
	glutPostRedisplay();
}

void RenderScene(void)
{
	GLfloat x,y,angle;
	int iPivot =1;           // add
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Begin - add ////////////////////////////////////////////
	if(iCull)
		glEnable(GL_CULL_FACE);   
	else
		glDisable(GL_CULL_FACE);  

	if(iDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	if(iOutline)
		glPolygonMode(GL_BACK,GL_LINE);
	else
		glPolygonMode(GL_BACK,GL_FILL); 
	//END - add ////////////////////////////////////////////

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLE_FAN); // add
	glVertex3f(0.0f, 0.0f, 75.0f); // add - 기준점

	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f)) 
	{		
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		if((iPivot %2) == 0) // add
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		iPivot++;           // add
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN); // add
	glVertex2f(0.0f, 0.0f);   // add - 기준점

	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
	{
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		if((iPivot %2) == 0)    // add
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		iPivot++;
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}	

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glColor3f(0.0f, 1.0f, 0.0f);
	glShadeModel(GL_FLAT); // add
	// glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CW);    // add 
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

	glutCreateWindow("Triangle");

	glutCreateMenu(ProcessMenu); // add - Create the Menu
	glutAddMenuEntry("깊이 테스트",1); 
	glutAddMenuEntry("은면 제거",2);
	glutAddMenuEntry("뒷면 라인 그리기",3);
	glutAttachMenu (GLUT_RIGHT_BUTTON);

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl); // add
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

}