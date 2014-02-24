#include "stdafx.h"
#include "PKMacro.h"
#include "PKDefine.h"
#include "PKLightManager.h"
#include "PKCameraManager.h"


CPKLightManager::CPKLightManager(void)
{
	ZeroMemory(&m_LightPos, sizeof(m_LightPos));
	ZeroMemory(&m_AmbientLight, sizeof(m_AmbientLight));
	ZeroMemory(&m_DiffuseLight, sizeof(m_DiffuseLight));
	ZeroMemory(&m_Specular, sizeof(m_Specular));
	ZeroMemory(&m_Matrix, sizeof(m_Matrix));
}


CPKLightManager::~CPKLightManager(void)
{
}

void CPKLightManager::SetPosition( GLfloat posX, GLfloat posY, GLfloat posZ, int index )
{
	if ( index < 0 || index >= MAX_LIGHT_COUNT )
		return;

	m_LightPos[index][0] = posX;
	m_LightPos[index][1] = posY;
	m_LightPos[index][2] = posZ;
	m_LightPos[index][3] = 1.0f;
}

void CPKLightManager::SetAmbient( GLfloat colorRed, GLfloat colorGreen, GLfloat colorBlue, GLfloat alpha )
{
	m_AmbientLight[0] = colorRed;
	m_AmbientLight[1] = colorGreen;
	m_AmbientLight[2] = colorBlue;
	m_AmbientLight[3] = alpha;
	glLightfv(GL_LIGHT0, GL_AMBIENT, m_AmbientLight);
	glLightfv(GL_LIGHT1, GL_AMBIENT, m_AmbientLight);
	glLightfv(GL_LIGHT2, GL_AMBIENT, m_AmbientLight);
	glLightfv(GL_LIGHT3, GL_AMBIENT, m_AmbientLight);
	glLightfv(GL_LIGHT4, GL_AMBIENT, m_AmbientLight);
	glLightfv(GL_LIGHT5, GL_AMBIENT, m_AmbientLight);
}

void CPKLightManager::SetDiffuse( GLfloat colorRed, GLfloat colorGreen, GLfloat colorBlue, GLfloat alpha )
{
	m_DiffuseLight[0] = colorRed;
	m_DiffuseLight[1] = colorGreen;
	m_DiffuseLight[2] = colorBlue;
	m_DiffuseLight[3] = alpha;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_DiffuseLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, m_DiffuseLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, m_DiffuseLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, m_DiffuseLight);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, m_DiffuseLight);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, m_DiffuseLight);
}

void CPKLightManager::SetSpecular( GLfloat colorRed, GLfloat colorGreen, GLfloat colorBlue, GLfloat alpha, GLint exponent )
{
	m_Specular[0] = colorRed;
	m_Specular[1] = colorGreen;
	m_Specular[2] = colorBlue;
	m_Specular[3] = alpha;

	glLightfv(GL_LIGHT0, GL_SPECULAR, m_Specular);
	glLightfv(GL_LIGHT1, GL_SPECULAR, m_Specular);
	glLightfv(GL_LIGHT2, GL_SPECULAR, m_Specular);
	glLightfv(GL_LIGHT3, GL_SPECULAR, m_Specular);
	glLightfv(GL_LIGHT4, GL_SPECULAR, m_Specular);
	glLightfv(GL_LIGHT5, GL_SPECULAR, m_Specular);
	glMateriali(GL_FRONT, GL_SHININESS, exponent);
}

void CPKLightManager::SetSpecularRef( GLfloat colorRed, GLfloat colorGreen, GLfloat colorBlue, GLfloat alpha )
{
	m_SpecularRef[0] = colorRed;
	m_SpecularRef[1] = colorGreen;
	m_SpecularRef[2] = colorBlue;
	m_SpecularRef[3] = alpha;

	glMaterialfv(GL_FRONT, GL_SPECULAR, m_SpecularRef);
}

void CPKLightManager::SetLight()
{
	GLmatrix matrix = CPKCameraManager::GetInstance()->GetMatrix();
	GLfloat	inputMatrix[16] = {0, }, invMatrix[16] = {0, }, resultMatrix[16] = {0, };

	for ( int i = 0 ; i < MATRIX_3D_ROW ; ++i )
	{
		for ( int j = 0 ; j < MATRIX_3D_COL ; ++j )
		{
			inputMatrix[j * 4 + i ] = matrix[i][j];
		}
	}

	CPKCameraManager::GetInstance()->MatrixInverse(inputMatrix, invMatrix);

	for ( int i = 0 ; i < MATRIX_3D_ROW ; ++i )
	{
		for ( int j = 0 ; j < MATRIX_3D_COL ; ++j )
		{
			m_Matrix[i][j] = invMatrix[j * 4 + i ];
		}
	}

	std::array<GLfloat, MATRIX_3D_COL> originPos;
	ZeroMemory(&originPos, sizeof(originPos));

	for ( int index = 0 ; index < MAX_LIGHT_COUNT ; ++index )
	{
		originPos[0] = m_LightPos[index][0];
		originPos[1] = m_LightPos[index][1];
		originPos[2] = m_LightPos[index][2];
		originPos[3] = m_LightPos[index][3];

		GLfloat resultPos[DIMENSION_3D] = {0, };

		for ( int i = 0 ; i < MATRIX_3D_COL ; ++i )
		{
			resultPos[0] += m_Matrix[0][i] * originPos[i];
			resultPos[1] += m_Matrix[1][i] * originPos[i];
			resultPos[2] += m_Matrix[2][i] * originPos[i];
			resultPos[3] += m_Matrix[3][i] * originPos[i];
		}

		resultPos[0] = (resultPos[0] / resultPos[3]);
		resultPos[1] = (resultPos[1] / resultPos[3]);
		resultPos[2] = (resultPos[2] / resultPos[3]);

		switch (index)
		{
		case 0:
			glLightfv( GL_LIGHT0 , GL_POSITION , resultPos );
			break;
		case 1:
			glLightfv( GL_LIGHT1 , GL_POSITION , resultPos );
			break;
		case 2:
			glLightfv( GL_LIGHT2 , GL_POSITION , resultPos );
			break;
		case 3:
			glLightfv( GL_LIGHT3 , GL_POSITION , resultPos );
			break;
		case 4:
			glLightfv( GL_LIGHT4 , GL_POSITION , resultPos );
			break;
		case 5:
			glLightfv( GL_LIGHT5 , GL_POSITION , resultPos );
			break;
		default:
			break;
		}
	}
}

void CPKLightManager::Init()
{
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}