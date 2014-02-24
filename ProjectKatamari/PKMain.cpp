// ProjectKatamari.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "PKMain.h"
#include "PKMacro.h"
#include "PKMainLoop.h"

//////////////////////////////////////////////////////////////////////////
// ������ �ܼ� ����

#ifdef _DEBUG
#include "PKPrintConsole.h"
#endif // _DEBUG

// �ܼ��� ���ַ��� ���� ����� �ּ�ó��
//////////////////////////////////////////////////////////////////////////


//�����Լ� ����
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


#ifdef _PRINT_CONSOLE


	// �޸� ����� �ɼ� �κ�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ������ �ܼ� ����� ���� �Ǿ� ���� ������ �̱������� �ܼ��� ������
	CPKPrintConsole::GetInstance();
#endif // _PRINT_CONSOLE

	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if ( SUCCEEDED( CoInitialize( NULL ) ) )
	{
		if ( SUCCEEDED( CPKMainLoop::GetInstance()->CreateMainLoopWindow() ) )
		{
			CPKMainLoop::GetInstance()->RunMessageLoop();
		}

		CoUninitialize();
	}

	return 0;
}
