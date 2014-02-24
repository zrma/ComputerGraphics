#include "stdafx.h"
#include <gl/glut.h>

void RenderScene(void)
{
	glClear( GL_COLOR_BUFFER_BIT );
	glFlush();
}

void SetupRC(void)
{
	glClearColor(0.0f, 0.0f,1.0f,1.0f);
}

void main(void)
{
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutCreateWindow( "Simple" );
	glutDisplayFunc( RenderScene );
	SetupRC();
	glutMainLoop();
}