#include "stdafx.h"
#include "PKMacro.h"
#include "PKRender.h"
#include "PKDummyRender.h"


CPKDummyRender::CPKDummyRender(void)
{
	CPKRender::GetInstance()->RenderBegin();
}


CPKDummyRender::~CPKDummyRender(void)
{
	CPKRender::GetInstance()->RenderEnd();
}
