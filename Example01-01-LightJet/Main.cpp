#include <stdlib.h>
#include <gl/glut.h>
#include <gl/GLTools.h>
#include <windows.h>
#include <math.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;	

void SetupRC()
{
	GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f }; // ADD
	glEnable(GL_DEPTH_TEST);	
	glFrontFace(GL_CCW);	
	glEnable(GL_CULL_FACE);	
	glEnable(GL_LIGHTING); 	
	// Setup and enable light 0
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight); //ADD
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight); //ADD 
	glEnable(GL_LIGHT0);                          //ADD
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;
	GLfloat lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };  
	//light position 

	glViewport(0,0,w,h);
	fAspect = (GLfloat)w/(GLfloat)h; 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,fAspect,1.0f,255.0f); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	//light position 
	glTranslatef(0.0f, 0.0f, -150.0f);
}

void DrawJet()
{
	GLTVector3 vNormal;

	// Nose Cone - Points straight down
	// Set material color
	glColor3ub(128, 128, 128);
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 60.0f);
	glVertex3f(-15.0f, 0.0f, 30.0f);
	glVertex3f(15.0f,0.0f,30.0f);


	// Verticies for this panel
	{
		GLTVector3 vPoints[3] = {{ 15.0f, 0.0f,  30.0f},
		{ 0.0f,  15.0f, 30.0f},
		{ 0.0f,  0.0f,  60.0f}};

		// Calculate the normal for the plane
		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}	


	{
		GLTVector3 vPoints[3] = {{ 0.0f, 0.0f, 60.0f },
		{ 0.0f, 15.0f, 30.0f },
		{ -15.0f, 0.0f, 30.0f }};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	// Body of the Plane ////////////////////////
	{
		GLTVector3 vPoints[3] = {{ -15.0f, 0.0f, 30.0f },
		{ 0.0f, 15.0f, 30.0f },
		{ 0.0f, 0.0f, -56.0f }};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = {{ 0.0f, 0.0f, -56.0f },
		{ 0.0f, 15.0f, 30.0f },
		{ 15.0f,0.0f,30.0f }};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(15.0f,0.0f,30.0f);
	glVertex3f(-15.0f, 0.0f, 30.0f);
	glVertex3f(0.0f, 0.0f, -56.0f);

	///////////////////////////////////////////////
	// Left wing
	// Large triangle for bottom of wing
	{
		GLTVector3 vPoints[3] = {{ 0.0f,2.0f,27.0f },
		{ -60.0f, 2.0f, -8.0f },
		{ 60.0f, 2.0f, -8.0f }};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	{
		GLTVector3 vPoints[3] = {{ 60.0f, 2.0f, -8.0f},
		{0.0f, 7.0f, -8.0f},
		{0.0f,2.0f,27.0f }};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = {{60.0f, 2.0f, -8.0f},
		{-60.0f, 2.0f, -8.0f},
		{0.0f,7.0f,-8.0f }};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = {{0.0f,2.0f,27.0f},
		{0.0f, 7.0f, -8.0f},
		{-60.0f, 2.0f, -8.0f}};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	// Tail section///////////////////////////////
	// Bottom of back fin
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-30.0f, -0.50f, -57.0f);
	glVertex3f(30.0f, -0.50f, -57.0f);
	glVertex3f(0.0f,-0.50f,-40.0f);

	{
		GLTVector3 vPoints[3] = {{ 0.0f,-0.5f,-40.0f },
		{30.0f, -0.5f, -57.0f},
		{0.0f, 4.0f, -57.0f }};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	{
		GLTVector3 vPoints[3] = {{ 0.0f, 4.0f, -57.0f },
		{ -30.0f, -0.5f, -57.0f },
		{ 0.0f,-0.5f,-40.0f }};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	{
		GLTVector3 vPoints[3] = {{ 30.0f,-0.5f,-57.0f },
		{ -30.0f, -0.5f, -57.0f },
		{ 0.0f, 4.0f, -57.0f }};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = {{ 0.0f,0.5f,-40.0f },
		{ 3.0f, 0.5f, -57.0f },
		{ 0.0f, 25.0f, -65.0f }};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	{
		GLTVector3 vPoints[3] = {{ 0.0f, 25.0f, -65.0f },
		{ -3.0f, 0.5f, -57.0f},
		{ 0.0f,0.5f,-40.0f }};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = {{ 3.0f,0.5f,-57.0f },
		{ -3.0f, 0.5f, -57.0f },
		{ 0.0f, 25.0f, -65.0f }};

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	glEnd();
}

void RenderScene(void)

{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state 
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, zDistance); 

	DrawJet();    // geometry to draw jet	 

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
	glutCreateWindow("Light Jet");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}
