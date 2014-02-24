#include "stdafx.h"
#include "PKMacro.h"
#include "PKDefine.h"
#include "PKRender.h"
#include "PKMainLoop.h"

CPKRender::CPKRender(void):
	m_hDC(nullptr),
	m_hglRC(nullptr)
{
}


CPKRender::~CPKRender(void)
{
}

BOOL CPKRender::SetPixelFormatRender( HDC hdc )
{
	GLuint	pixelFormat = 0;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,									// default version
		PFD_DRAW_TO_WINDOW |				// support window
		PFD_SUPPORT_OPENGL |				// support OpenGL
		PFD_GENERIC_FORMAT |
		PFD_DOUBLEBUFFER,					// double buffered
		PFD_TYPE_RGBA,						// RGBA type
		32,									// 32-bit color depth
		0, 0, 0, 0, 0, 0,					// color bits ignored
		8,									// no alpha buffer
		0,									// shift bit ignored
		8,									// no accumulation buffer
		0, 0, 0, 0,							// accum bitsignored
		16,									// 16-bit z-buffer
		0,									// no stencil buffer
		0,									// no auxiliary buffer
		PFD_MAIN_PLANE,						// main layer
		0,									// reserved
		0, 0, 0								// layer masksignored
	};

	if ( (pixelFormat = ChoosePixelFormat(hdc, &pfd) ) == FALSE )
	{
		MessageBoxW( CPKMainLoop::GetInstance()->GetHwnd(), L"ChoosePixelFormat failed", L"Error", MB_OK );
		return FALSE;
	}
	if( (SetPixelFormat( m_hDC , pixelFormat , &pfd) ) == FALSE )		// hDC의 Pixel Format을 설정한다. Are We Able To Set The Pixel Format?

	{
		MessageBoxW( CPKMainLoop::GetInstance()->GetHwnd(), L"ChoosePixelFormat failed", L"Error", MB_OK );
		return FALSE;								// Return FALSE
	}

	return TRUE;
}

void CPKRender::Create()
{
	m_hDC = GetDC( CPKMainLoop::GetInstance()->GetHwnd() );

	if( !SetPixelFormatRender(m_hDC) )
	{
		return;
	}
	// create rendering contextand make it current

	m_hglRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC,m_hglRC);
}

void CPKRender::Release()
{
	//deselect rendering context and delete it
	wglMakeCurrent( m_hDC , NULL );
	wglDeleteContext( m_hglRC );
}

void CPKRender::InitOpenGL()
{
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f );
	glClearDepth( 1.f );
	glEnable( GL_DEPTH_TEST );
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING); 		// Enable lighting

	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST );

	// reset the viewport to new dimentions
	glViewport( 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	// calculate aspect ratio of the window
	gluPerspective ( 60.0f, (GLfloat)SCREEN_SIZE_X / SCREEN_SIZE_Y, 1.0f, 1000.0f );
	
	//set modelview matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

void CPKRender::RenderBegin()
{
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

void CPKRender::RenderEnd()
{
	glEnd();
	SwapBuffers( m_hDC );
}