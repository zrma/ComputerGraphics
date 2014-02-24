// ProjectKatamari.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "PKMain.h"
#include "PKMacro.h"
#include "PKMainLoop.h"

//////////////////////////////////////////////////////////////////////////
// 디버깅용 콘솔 제어

#ifdef _DEBUG
#include "PKPrintConsole.h"
#endif // _DEBUG

// 콘솔을 없애려면 위의 헤더를 주석처리
//////////////////////////////////////////////////////////////////////////


//메인함수 시작
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


#ifdef _PRINT_CONSOLE


	// 메모리 디버깅 옵션 부분
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 디버깅용 콘솔 헤더가 포함 되어 있을 때에만 싱글톤으로 콘솔을 생성함
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
