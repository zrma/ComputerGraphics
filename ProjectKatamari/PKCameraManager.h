#pragma once

#include "PKDefine.h"
#include "PKEnumSet.h"

typedef array2d_<GLfloat, MATRIX_3D_ROW, MATRIX_3D_COL>::type GLmatrix;

class CPKCameraManager
{
	SINGLETON(CPKCameraManager);
private:
	CPKCameraManager(void);
	~CPKCameraManager(void);

public:
	
	void		Init();
	void		Update();

	GLmatrix	GetMatrix() { return m_Matrix; }
	void		MatrixInverse(GLfloat *OpenGLmatIn, GLfloat *matOut);

	void		SetFocus( int x, int y ) { m_FocusX = x; m_FocusY = y; }

private:
	void		CalcMatrix( TransType trans, int sign );
	int			m_FocusX;
	int			m_FocusY;

	GLmatrix	m_Matrix;
};

