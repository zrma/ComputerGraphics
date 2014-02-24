#pragma once
#include "PKMacro.h"
#include "PKDefine.h"
typedef array2d_<GLfloat, MATRIX_3D_ROW, MATRIX_3D_COL>::type GLmatrix;

class CPKObject
{
public:
	CPKObject(void);
	virtual ~CPKObject(void);

public:
	virtual void	Update() = 0;
	virtual void	Render() const = 0;

	void		SetPosition(GLfloat positionX, GLfloat positionY, GLfloat positionZ);
	void		SetColor(GLubyte colorRed, GLubyte colorGreen, GLubyte colorBlue);

	void		SetParent( CPKObject* parent ) { m_Parent = parent; }

	GLfloat		GetPositionX() { return m_PositionX; }
	GLfloat		GetPositionY() { return m_PositionY; }
	GLfloat		GetPositionZ() { return m_PositionZ; }

protected:
	GLfloat		m_PositionX;
	GLfloat		m_PositionY;
	GLfloat		m_PositionZ;
	GLubyte		m_ColorRed;
	GLubyte		m_ColorGreen;
	GLubyte		m_ColorBlue;

	GLmatrix	m_Matrix;
	CPKObject*	m_Parent;
};
