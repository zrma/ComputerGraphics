#pragma once
#include "PKEnumSet.h"

class AUX_RGBImageRec;

class CPKTextureManager
{
	SINGLETON(CPKTextureManager);
private:
	CPKTextureManager(void);
	~CPKTextureManager(void);

public:
	void				Init();
	void				TextureMappingBegin( PlanetType type );
	void				TextureMappingEnd();

private:
	GLuint				m_TexID[PLANET_TYPE_MAX];

	std::array<AUX_RGBImageRec*, PLANET_TYPE_MAX>	m_TexRec;
};

