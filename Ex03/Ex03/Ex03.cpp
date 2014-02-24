// Ex03.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <gl\glut.h>


//추가 코드 포함 화면 그리기
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//사각형 그리기 line1 = color / line2 = 사각형 그리기
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(-50.0f, 50.0f, 50.0f, -50.0f);
	glFlush();
}

//화면에 들어갈 렌더 문맥 설정
void renderScene(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

//창 크기에 따라 변경되도록
void fittingWindowSize(GLsizei width, GLsizei height)
{
	//높이가 0이면 0으로 나누는 오류 예외처리
	if(height == 0)
	{
		height = 1;
	}
	//투영 행렬 설정 모드로 변경
	glMatrixMode(GL_PROJECTION);
	//투영 행렬을 단위행렬로 설정
	glLoadIdentity();
	//투영 행렬 설정
	GLfloat aspect = (GLfloat) width / (GLfloat) height;
	GLfloat wantBoxHeight = 200.0f;
	GLfloat clipBoxHalfHeight = wantBoxHeight * 0.5f;
	GLfloat clipBoxHalfWidth = clipBoxHalfHeight * aspect;
	glOrtho(-clipBoxHalfWidth, clipBoxHalfWidth, -clipBoxHalfHeight, clipBoxHalfHeight, 1.0f, -1.0f);
	
	//뷰포트 설정
	glViewport(0, 0, width, height);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//화면에 직접 그리기 | RGB 색상으로
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//윈도우 생성 함수
	glutCreateWindow("OpenGL TEST");

	//화면 그리기
	glutDisplayFunc(display);

	//크기 재구성 함수 설정
	glutReshapeFunc(fittingWindowSize);

	//화면 렌더 문맥 설정
	renderScene();

	//프로그램 루프 시작
	glutMainLoop();

	return 0;
}

