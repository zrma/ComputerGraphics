#include "stdafx.h"
#include "PKMacro.h"
#include "PKCameraManager.h"
#include "PKInputManager.h"

CPKCameraManager::CPKCameraManager(void):
	m_FocusX(SCREEN_SIZE_X / 2), m_FocusY(SCREEN_SIZE_Y / 2)
{
	ZeroMemory( &m_Matrix, sizeof(m_Matrix) );
	m_Matrix[0][0] = m_Matrix[1][1] = m_Matrix[2][2] = m_Matrix[3][3] = 1.0;
}


CPKCameraManager::~CPKCameraManager(void)
{
}

void CPKCameraManager::Update()
{
	if ( m_FocusX > SCREEN_SIZE_X / 2 + 5 )
	{
		CPKInputManager::GetInstance()->SetKeyStatusByKey(KEY_TABLE_TURN_RIGHT, KEY_STATUS_PRESSED);
	}
	else if ( m_FocusX < SCREEN_SIZE_X / 2 - 5 )
	{
		CPKInputManager::GetInstance()->SetKeyStatusByKey(KEY_TABLE_TURN_LEFT, KEY_STATUS_PRESSED);
	}
	else if ( m_FocusY > SCREEN_SIZE_Y / 2 + 2 )
	{
		CPKInputManager::GetInstance()->SetKeyStatusByKey(KEY_TABLE_TURN_DOWN, KEY_STATUS_PRESSED);
	}
	else if ( m_FocusY < SCREEN_SIZE_Y / 2 - 2 )
	{
		CPKInputManager::GetInstance()->SetKeyStatusByKey(KEY_TABLE_TURN_UP, KEY_STATUS_PRESSED);
	}

	if ( CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_SPACE) == KEY_STATUS_DOWN || 
		CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_SPACE) == KEY_STATUS_PRESSED  )
	{
		ZeroMemory( &m_Matrix, sizeof(m_Matrix) );
		m_Matrix[0][0] = m_Matrix[1][1] = m_Matrix[2][2] = m_Matrix[3][3] = 1.0;
	}
	if ( CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_TURN_LEFT) == KEY_STATUS_DOWN || 
		CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_TURN_LEFT) == KEY_STATUS_PRESSED  )
	{
		CalcMatrix( TRANSE_TYPE_ROTATE_Y , 1 );
	}
	if ( CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_TURN_RIGHT) == KEY_STATUS_DOWN || 
		CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_TURN_RIGHT) == KEY_STATUS_PRESSED )
	{
		CalcMatrix( TRANSE_TYPE_ROTATE_Y , -1 );
	}
	if ( CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_TURN_UP) == KEY_STATUS_DOWN || 
		CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_TURN_UP) == KEY_STATUS_PRESSED )
	{
		CalcMatrix( TRANSE_TYPE_ROTATE_X , 1 );
	}
	if ( CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_TURN_DOWN) == KEY_STATUS_DOWN || 
		CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_TURN_DOWN) == KEY_STATUS_PRESSED )
	{
		CalcMatrix( TRANSE_TYPE_ROTATE_X , -1 );
	}
	//////////////////////////////////////////////////////////////////////////
	if ( CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_ROTATE_LEFT) == KEY_STATUS_DOWN || 
		CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_ROTATE_LEFT) == KEY_STATUS_PRESSED )
	{
		CalcMatrix( TRANSE_TYPE_ROTATE_Z , 1 );
	}
	if ( CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_ROTATE_RIGHT) == KEY_STATUS_DOWN || 
		CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_ROTATE_RIGHT) == KEY_STATUS_PRESSED )
	{
		CalcMatrix( TRANSE_TYPE_ROTATE_Z , -1 );
	}
	//////////////////////////////////////////////////////////////////////////
	if ( CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_GO_FRONT) == KEY_STATUS_DOWN || 
		CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_GO_FRONT) == KEY_STATUS_PRESSED )
	{
		CalcMatrix( TRANSE_TYPE_TRANSLATE_Z , -1 );
	}
	if ( CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_GO_BACK) == KEY_STATUS_DOWN || 
		CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_GO_BACK) == KEY_STATUS_PRESSED )
	{
		CalcMatrix( TRANSE_TYPE_TRANSLATE_Z , 1 );
	}
	if ( CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_GO_LEFT) == KEY_STATUS_DOWN || 
		CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_GO_LEFT) == KEY_STATUS_PRESSED )
	{
		CalcMatrix( TRANSE_TYPE_TRANSLATE_X , -1 );
	}
	if ( CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_GO_RIGHT) == KEY_STATUS_DOWN || 
		CPKInputManager::GetInstance()->GetKeyStatusByKey(KEY_TABLE_GO_RIGHT) == KEY_STATUS_PRESSED )
	{
		CalcMatrix( TRANSE_TYPE_TRANSLATE_X , 1 );
	}
}

// 참고 사이트 http://harinadha.wordpress.com/2012/05/14/inversetransform/
void CPKCameraManager::MatrixInverse(GLfloat *OpenGLmatIn, GLfloat *matOut)
{
	GLmatrix	matIn;

	// OpenGL matrix is column major matrix in 1x16 array. Convert it to row major 4x4 matrix
	for ( int m = 0 , k = 0 ; m <= 3 , k < 16 ; m++ )
	{
		for ( int n = 0 ; n <= 3 ; n++ )
		{
			matIn[m][n] = OpenGLmatIn[k];
			k++;
		}
	}
	// 3x3 rotation Matrix Transpose ( it is equal to invering rotations)
	// Since rotation matrix is anti-symmetric matrix, transpose is equal to Inverse.
	for ( int i = 0 ; i < 3 ; i++ )
	{
		for( int j = 0 ; j < 3 ; j++ )
		{
			matOut[j * 4 + i] = matIn[i][j];
		}
	}
	// Negate the translations ( equal to inversing translations)
	std::array<GLfloat, 3> vTmp;
	ZeroMemory(&vTmp, sizeof(vTmp));

	vTmp[0] = -matIn[3][0];
	vTmp[1] = -matIn[3][1];
	vTmp[2] = -matIn[3][2];
	// Roatate this vector using the above newly constructed rotation matrix
	matOut[3 * 4 + 0] = vTmp[0]*matOut[0 * 4 + 0] + vTmp[1]*matOut[1 * 4 + 0] + vTmp[2]*matOut[2 * 4 + 0];
	matOut[3 * 4 + 1] = vTmp[0]*matOut[0 * 4 + 1] + vTmp[1]*matOut[1 * 4 + 1] + vTmp[2]*matOut[2 * 4 + 1];
	matOut[3 * 4 + 2] = vTmp[0]*matOut[0 * 4 + 2] + vTmp[1]*matOut[1 * 4 + 2] + vTmp[2]*matOut[2 * 4 + 2];

	// Take care of the unused part of the OpenGL 4x4 matrix
	matOut[0 * 4 + 3] = matOut[1 * 4 + 3] = matOut[2 * 4 + 3] = 0.0f;
	matOut[3 * 4 + 3] = 1.0f;
}

void CPKCameraManager::CalcMatrix( TransType trans, int sign )
{
	GLfloat matrix[MATRIX_3D_ROW * MATRIX_3D_COL] = {0, };
	glPushMatrix();

	GLfloat	inputMatrix[16] = {0, };

	for ( int i = 0 ; i < MATRIX_3D_ROW ; ++i )
	{
		for ( int j = 0 ; j < MATRIX_3D_COL ; ++j )
		{
			inputMatrix[j * 4 + i ] = m_Matrix[i][j];
		}
	}

	glLoadMatrixf(inputMatrix);

	switch (trans)
	{
	case TRANSE_TYPE_TRANSLATE_X:
		glTranslatef(1.0f * sign, 0.0f, 0.0f);
		break;
	case TRANSE_TYPE_TRANSLATE_Y:
		glTranslatef(0.0f, 0.0f * sign, 0.0f);
		break;
	case TRANSE_TYPE_TRANSLATE_Z:
		glTranslatef(0.0f, 0.0f, 1.0f * sign);
		break;
	case TRANSE_TYPE_ROTATE_X:
		glRotatef(1.0f * sign, 1.0f, 0.0f, 0.0f);
		break;
	case TRANSE_TYPE_ROTATE_Y:
		glRotatef(1.0f * sign, 0.0f, 1.0f, 0.0f);
		break;
	case TRANSE_TYPE_ROTATE_Z:
		glRotatef(1.0f * sign, 0.0f, 0.0f, 1.0f);
		break;
	default:
		break;
	}
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

	for ( int i = 0 ; i < MATRIX_3D_ROW ; ++i )
	{
		for ( int j = 0 ; j < MATRIX_3D_COL ; ++j )
		{
			printConsole( " [%09.4f] " , matrix[j * 4 + i] );
			m_Matrix[i][j] = matrix[j * 4 + i ];
		}
		printConsole ( " \n" );
	}
}
