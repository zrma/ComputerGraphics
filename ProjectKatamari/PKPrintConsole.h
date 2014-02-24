#pragma once

#ifndef _PRINT_CONSOLE
#define _PRINT_CONSOLE
#endif

class CPKPrintConsole
{
	SINGLETON(CPKPrintConsole);
private:
	CPKPrintConsole(void);
	~CPKPrintConsole(void);
};

