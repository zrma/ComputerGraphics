#include "stdafx.h"
#include "PKChildSphere.h"
#include "PKCameraManager.h"
#include "PKTextureManager.h"

CPKChildSphere::CPKChildSphere(void):
	m_Size(0), m_Radius(0), m_Angle(0), m_Speed(0), m_Gradient(0), m_Spin(0), m_NowSpin(0),
	m_Type(PLANET_TYPE_NONE),
	m_Sphere(nullptr)
{
	m_Angle = rand() % 360;
	m_Sphere = gluNewQuadric();
	gluQuadricDrawStyle( m_Sphere , GLU_FILL );
	gluQuadricTexture( m_Sphere , GL_TRUE );
}


CPKChildSphere::~CPKChildSphere(void)
{
}

void CPKChildSphere::Render() const
{
	glPushMatrix();
	glLoadIdentity();

	GLmatrix matrix = CPKCameraManager::GetInstance()->GetMatrix();
	GLfloat	inputMatrix[16] = {0, }, invMatrix[16] = {0, };

	for ( int i = 0 ; i < MATRIX_3D_ROW ; ++i )
	{
		for ( int j = 0 ; j < MATRIX_3D_COL ; ++j )
		{
			inputMatrix[j * 4 + i ] = matrix[i][j];
		}
	}

	CPKCameraManager::GetInstance()->MatrixInverse(inputMatrix, invMatrix);
	glMultMatrixf(invMatrix);
	
	glColor3ub( m_ColorRed, m_ColorGreen, m_ColorBlue );
	glTranslatef( m_PositionX, m_PositionY, m_PositionZ );

	if ( m_Type != PLANET_TYPE_NONE )
	{
		CPKTextureManager::GetInstance()->TextureMappingBegin( m_Type );
	}

	glRotatef(m_NowSpin, 0.0f, 1.0f, 0.0f);
	// 자전 효과를 위한 변환

	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	// 텍스쳐 누워져 있는 것을 바로세우기 위해서 x축을 기준으로 90도 회전

	gluSphere(m_Sphere, m_Size, 40, 40);
	
	if ( m_Type != PLANET_TYPE_NONE )
	{
		CPKTextureManager::GetInstance()->TextureMappingEnd();
	}

	glPopMatrix();
}

void CPKChildSphere::Update()
{
	m_NowSpin += m_Spin;

	if ( m_NowSpin > 360 )
	{
		m_NowSpin -= 360;
	}
	if ( m_NowSpin < 0 )
	{
		m_NowSpin += 360;
	}

	if ( m_Parent == nullptr )
		return;

	m_Angle += m_Speed;
	
	if ( m_Angle > 360 )
	{
		m_Angle -= 360;
	}
	if ( m_Angle < 0 )
	{
		m_Angle += 360;
	}

	GLfloat matrix[MATRIX_3D_ROW * MATRIX_3D_COL] = {0, };
	glPushMatrix();
	glLoadIdentity();
	
	glRotatef( m_Gradient, 1.0f, 0.0f, 0.0f);
	glRotatef( m_Angle, 0.0f, 1.0f, 0.0f );
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

	for ( int i = 0 ; i < MATRIX_3D_ROW ; ++i )
	{
		for ( int j = 0 ; j < MATRIX_3D_COL ; ++j )
		{
			m_Matrix[i][j] = matrix[j * 4 + i ];
		}
	}

	std::array<GLfloat, MATRIX_3D_COL> originPos;
	ZeroMemory(&originPos, sizeof(originPos));

	originPos[0] = 0;
	originPos[1] = 0;
	originPos[2] = m_Radius;
	originPos[3] = 1;

	GLfloat zValue = 0;
	m_PositionX = m_PositionY = m_PositionZ = 0;

	for ( int i = 0 ; i < MATRIX_3D_COL ; ++i )
	{
		m_PositionX += m_Matrix[0][i] * originPos[i];
		m_PositionY += m_Matrix[1][i] * originPos[i];
		m_PositionZ += m_Matrix[2][i] * originPos[i];
		zValue += m_Matrix[3][i] * originPos[i];
	}

	m_PositionX = (m_PositionX / zValue) + m_Parent->GetPositionX();
	m_PositionY = (m_PositionY / zValue) + m_Parent->GetPositionY();
	m_PositionZ = (m_PositionZ / zValue) + m_Parent->GetPositionZ();
}

void CPKChildSphere::SetParent( CPKObject* parent )
{
	super::SetParent(parent);

	m_PositionX = m_Parent->GetPositionX();
	m_PositionY = m_Parent->GetPositionY();
	m_PositionZ = m_Parent->GetPositionZ();
}
