#include "stdafx.h"
#include "PKMacro.h"
#include "PKPrintConsole.h"


CPKPrintConsole::CPKPrintConsole(void)
{
	AllocConsole();
	FILE* pFile; 
	freopen_s(&pFile, "CONOUT$", "wb", stdout);
}


CPKPrintConsole::~CPKPrintConsole(void)
{
	FreeConsole();
}
