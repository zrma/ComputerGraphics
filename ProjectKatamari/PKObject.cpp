#include "stdafx.h"
#include "PKObject.h"

CPKObject::CPKObject(void):
	m_PositionX(0), m_PositionY(0), m_PositionZ(0),
	m_ColorRed(0), m_ColorGreen(0), m_ColorBlue(0),
	m_Parent(nullptr)
{
	ZeroMemory( &m_Matrix, sizeof(m_Matrix) );
	m_Matrix[0][0] = m_Matrix[1][1] = m_Matrix[2][2] = m_Matrix[3][3] = 1.0;
}


CPKObject::~CPKObject(void)
{
}

void CPKObject::SetPosition( GLfloat positionX, GLfloat positionY, GLfloat positionZ )
{
	m_PositionX = positionX;
	m_PositionY = positionY;
	m_PositionZ = positionZ;
}

void CPKObject::SetColor( GLubyte colorRed, GLubyte colorGreen, GLubyte colorBlue )
{
	m_ColorRed = colorRed;
	m_ColorGreen = colorGreen;
	m_ColorBlue = colorBlue;
}