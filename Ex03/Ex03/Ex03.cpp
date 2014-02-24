// Ex03.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <gl\glut.h>


//�߰� �ڵ� ���� ȭ�� �׸���
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//�簢�� �׸��� line1 = color / line2 = �簢�� �׸���
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(-50.0f, 50.0f, 50.0f, -50.0f);
	glFlush();
}

//ȭ�鿡 �� ���� ���� ����
void renderScene(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

//â ũ�⿡ ���� ����ǵ���
void fittingWindowSize(GLsizei width, GLsizei height)
{
	//���̰� 0�̸� 0���� ������ ���� ����ó��
	if(height == 0)
	{
		height = 1;
	}
	//���� ��� ���� ���� ����
	glMatrixMode(GL_PROJECTION);
	//���� ����� ������ķ� ����
	glLoadIdentity();
	//���� ��� ����
	GLfloat aspect = (GLfloat) width / (GLfloat) height;
	GLfloat wantBoxHeight = 200.0f;
	GLfloat clipBoxHalfHeight = wantBoxHeight * 0.5f;
	GLfloat clipBoxHalfWidth = clipBoxHalfHeight * aspect;
	glOrtho(-clipBoxHalfWidth, clipBoxHalfWidth, -clipBoxHalfHeight, clipBoxHalfHeight, 1.0f, -1.0f);
	
	//����Ʈ ����
	glViewport(0, 0, width, height);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//ȭ�鿡 ���� �׸��� | RGB ��������
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//������ ���� �Լ�
	glutCreateWindow("OpenGL TEST");

	//ȭ�� �׸���
	glutDisplayFunc(display);

	//ũ�� �籸�� �Լ� ����
	glutReshapeFunc(fittingWindowSize);

	//ȭ�� ���� ���� ����
	renderScene();

	//���α׷� ���� ����
	glutMainLoop();

	return 0;
}

