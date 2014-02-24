#include "stdafx.h"
#include "PKMacro.h"
#include "bmp.h"
#include "PKTextureManager.h"

CPKTextureManager::CPKTextureManager(void)
{
	ZeroMemory(&m_TexRec, sizeof(m_TexRec));
	ZeroMemory(&m_TexID, sizeof(m_TexID));
}


CPKTextureManager::~CPKTextureManager(void)
{
	for ( auto& toBeDelete : m_TexRec )
	{
		SafeDelete(toBeDelete);
	}
}

void CPKTextureManager::Init()
{
	m_TexRec[PLANET_TYPE_UNIVERSE] = auxDIBImageLoad("./Bitmap/space.bmp");
	m_TexRec[PLANET_TYPE_SUN] = auxDIBImageLoad("./Bitmap/sun.bmp");
	m_TexRec[PLANET_TYPE_MERCURY] = auxDIBImageLoad("./Bitmap/mercury.bmp");
	m_TexRec[PLANET_TYPE_VENUS] = auxDIBImageLoad("./Bitmap/venus.bmp");
	m_TexRec[PLANET_TYPE_EARTH] = auxDIBImageLoad("./Bitmap/earth.bmp");
	m_TexRec[PLANET_TYPE_MOON] = auxDIBImageLoad("./Bitmap/moon.bmp");
	m_TexRec[PLANET_TYPE_MARS] = auxDIBImageLoad("./Bitmap/mercury.bmp");

	glGenTextures(PLANET_TYPE_MAX, m_TexID);

	for ( int i = PLANET_TYPE_NONE + 1 ; i < PLANET_TYPE_MAX ; ++i )
	{
		if ( m_TexRec[i] )
		{
			glBindTexture(GL_TEXTURE_2D, m_TexID[i]);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_TexRec[i]->sizeX, m_TexRec[i]->sizeY, 1, GL_RGB, GL_UNSIGNED_BYTE, m_TexRec[i]->data);
		}
	}
}

void CPKTextureManager::TextureMappingBegin( PlanetType type )
{
	glBindTexture(GL_TEXTURE_2D, m_TexID[type]);
	glEnable(GL_TEXTURE_2D);
}

void CPKTextureManager::TextureMappingEnd()
{
	glDisable(GL_TEXTURE_2D);
}


