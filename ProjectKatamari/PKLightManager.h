#pragma once

typedef array2d_<GLfloat, MATRIX_3D_ROW, MATRIX_3D_COL>::type GLmatrix;

class CPKLightManager
{
	SINGLETON(CPKLightManager);
private:
	CPKLightManager(void);
	~CPKLightManager(void);

public:
	void		SetPosition( GLfloat posX, GLfloat posY, GLfloat PosZ, int index );
	void		SetAmbient( GLfloat colorRed, GLfloat colorGreen, GLfloat colorBlue, GLfloat alpha );
	void		SetDiffuse( GLfloat colorRed, GLfloat colorGreen, GLfloat colorBlue, GLfloat alpha );
	void		SetSpecular( GLfloat colorRed, GLfloat colorGreen, GLfloat colorBlue, GLfloat alpha, GLint exponent );
	void		SetSpecularRef( GLfloat colorRed, GLfloat colorGreen, GLfloat colorBlue, GLfloat alpha );
	void		Init();
	void		SetLight();

private:
	std::array<GLfloat[DIMENSION_3D], MAX_LIGHT_COUNT>	m_LightPos;
	
	GLfloat		m_AmbientLight[DIMENSION_3D];
	GLfloat		m_DiffuseLight[DIMENSION_3D];
	GLfloat		m_Specular[DIMENSION_3D];
	GLfloat		m_SpecularRef[DIMENSION_3D];
	
	GLmatrix	m_Matrix;
};

