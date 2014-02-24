#pragma once
#include "PKObject.h"

typedef CPKObject super;

class CPKChildBackground :
	public CPKObject
{
public:
	CPKChildBackground(void);
	virtual ~CPKChildBackground(void);

	virtual void	Update();
	virtual void	Render() const;
};

