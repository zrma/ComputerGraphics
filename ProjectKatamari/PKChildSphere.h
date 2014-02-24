#pragma once
#include "PKEnumSet.h"
#include "PKObject.h"

typedef CPKObject super;

typedef struct {
	float x, y, z;
	DWORD color;
	float u, v;
} VERTEX;

class CPKChildSphere :
	public CPKObject
{
public:
	CPKChildSphere(void);
	virtual ~CPKChildSphere(void);

	virtual void	Render() const;
	virtual	void	Update();

	void			SetSize(GLfloat size) { m_Size = size; }
	void			SetRadius(GLfloat radius) { m_Radius = radius; }
	void			SetParent( CPKObject* parent );
	void			SetSpeed(GLfloat speed) { m_Speed = speed; }
	void			SetGradient(GLfloat gradient) { m_Gradient = gradient; }
	void			SetSpin(GLfloat spin) { m_Spin = spin; }
	void			SetType(PlanetType type) { m_Type = type; }

private:
	GLfloat				m_Size;
	GLfloat				m_Radius;
	GLfloat				m_Angle;
	GLfloat				m_Speed;
	GLfloat				m_Gradient;
	GLfloat				m_Spin;
	GLfloat				m_NowSpin;

	PlanetType			m_Type;
	GLUquadricObj*		m_Sphere;
};

