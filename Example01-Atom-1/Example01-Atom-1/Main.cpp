#include <stdlib.h>
#include <gl/glut.h>
#include <windows.h>
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC()
{
	GLfloat		ambientLight[] = { 0.2f, 0.1f, 0.1f, 1.0f };
	GLfloat		diffuseLight[] = { 0.3f, 0.2f, 0.2f, 1.0f }; // ADD
	GLfloat		lightPos1[] = { 0.0f, 0.0f, 200.0f, 0.5f };
	GLfloat		lightPos2[] = { 0.0f, 0.0f, -200.0f, 0.5f };
	GLfloat		lightPos3[] = { 200.0f, 0.0f, 0.0f, 0.5f };
	GLfloat		lightPos4[] = { -200.0f, 0.0f, 0.0f, 0.1f };
	GLfloat		specular[] = { 0.5f, 0.3f, 0.3f, 1.0f };

	glEnable(GL_DEPTH_TEST);	
	glFrontFace(GL_CCW);	
	glEnable(GL_CULL_FACE);	
	
	glEnable(GL_LIGHTING); 	
	// Setup and enable light 0
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight); //ADD
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight); //ADD 
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos1);
	glEnable(GL_LIGHT0);                          //ADD

	glLightfv(GL_LIGHT1,GL_AMBIENT,ambientLight); //ADD
	glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuseLight); //ADD 
	glLightfv(GL_LIGHT1,GL_POSITION,lightPos2);
	glEnable(GL_LIGHT1);                          //ADD

	glLightfv(GL_LIGHT2,GL_AMBIENT,ambientLight); //ADD
	glLightfv(GL_LIGHT2,GL_DIFFUSE,diffuseLight); //ADD 
	glLightfv(GL_LIGHT2,GL_POSITION,lightPos3);
	glEnable(GL_LIGHT2);                          //ADD

	glLightfv(GL_LIGHT3,GL_AMBIENT,ambientLight); //ADD
	glLightfv(GL_LIGHT3,GL_DIFFUSE,diffuseLight); //ADD 
	glLightfv(GL_LIGHT3,GL_POSITION,lightPos4);
	glEnable(GL_LIGHT3);                          //ADD

	glEnable(GL_COLOR_MATERIAL); 	
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMateriali(GL_FRONT, GL_SHININESS, 80);
	
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

	gluPerspective(60.0f, fAspect, 1.0f, 700.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene() // add – draw 3 sphere 
{	
	// Earth and Moon angle of revolution
	static float fMoonRot = 0.0f;
	static float fEarthRot = 0.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix(); // 초기 메트릭스 저장

	//시점을 뒤로 300만큼 이동해서 관측 시점 지정
	glTranslatef(0.0f, 0.0f, -300.0f);	
	//태양을 그린다
	glColor3ub(255, 255, 0);
	glutSolidSphere(35.0f, 30, 17);

	// y축으로 일정하게 증가해서 회전하는 좌표계를 세팅
	glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);

	glTranslatef(120.0f,0.0f,0.0f); // x 방향으로 105만큼 평행이동

	glColor3ub(0,0,255); 	 // 지구를 그린다
	glutSolidSphere(15.0f, 30, 17);
	
	//최초 메트릭스로 변경
	
	// glTranslatef(0.0f, 0.0f, -300.0f);	

	// y축으로 일정하게 증가해서 회전하는 좌표계를 세팅
	glRotatef(fMoonRot, 0.0f,1.0f,0.0f);
	glTranslatef(0.0f,0.0f,30.0f);

	glColor3ub (240,240,240);
	glutSolidSphere(8.0f,30,17);

	glPopMatrix();


	fMoonRot+= 15.0f;

	// Step earth orbit 5 degrees
	fEarthRot += 5.0f;
	if(fEarthRot > 360.0f)
		fEarthRot = 0.0f;

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
