#include "stdafx.h"
#include "PKChildBackground.h"
#include "PKTextureManager.h"


CPKChildBackground::CPKChildBackground(void)
{
}


CPKChildBackground::~CPKChildBackground(void)
{
}

void CPKChildBackground::Update()
{

}

void CPKChildBackground::Render() const
{
	glPushMatrix();
	glLoadIdentity();
	
	glTranslatef(0, 0, -990);
	
	glColor3ub(255, 255, 255);
	
	CPKTextureManager::GetInstance()->TextureMappingBegin( PLANET_TYPE_UNIVERSE );
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0 , 0.0);
	glVertex2f(-SCREEN_SIZE_X , -SCREEN_SIZE_Y);
	glTexCoord2f(1.0 , 0.0);
	glVertex2f(SCREEN_SIZE_X , -SCREEN_SIZE_Y);
	glTexCoord2f(1.0 , 1.0);
	glVertex2f(SCREEN_SIZE_X , SCREEN_SIZE_Y);
	glTexCoord2f(0.0 , 1.0);
	glVertex2f(-SCREEN_SIZE_X , SCREEN_SIZE_Y);
	glEnd();

	CPKTextureManager::GetInstance()->TextureMappingEnd();
	
	glPopMatrix();
}
