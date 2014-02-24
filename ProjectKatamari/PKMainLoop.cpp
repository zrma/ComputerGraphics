#include "stdafx.h"
#include "Resource.h"
#include "PKMacro.h"
#include "PKDefine.h"
#include "PKConst.h"
#include "PKMainLoop.h"
#include "PKRender.h"
#include "PKDummyRender.h"
#include "PKObjectManager.h"
#include "PKInputManager.h"
#include "PKChildSphere.h"
#include "PKCameraManager.h"
#include "PKLightManager.h"
#include "PKTextureManager.h"
#include "PKChildBackground.h"

CPKMainLoop::CPKMainLoop(void):
	m_Hwnd(nullptr),
	m_PrevTime(0)
{
}


CPKMainLoop::~CPKMainLoop(void)
{
	CPKRender::GetInstance()->Release();
}

HRESULT CPKMainLoop::CreateMainLoopWindow()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= CPKMainLoop::WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	// wcex.hInstance		= HINST_THISCOMPONENT;
	wcex.hInstance		= GetModuleHandle(NULL);
	wcex.hIcon			= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_PROJECTKATAMARI));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL; // 배경 색상 부분 NULL로 설정
	wcex.lpszMenuName	= NULL;	// 메뉴 생성 부분 NULL로 설정
	wcex.lpszClassName	= CLASS_NAME;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);

	int START_POSITION_X = 0;
	int START_POSITION_Y = 0;

	START_POSITION_X = GetSystemMetrics(SM_CXSCREEN);
	START_POSITION_Y = GetSystemMetrics(SM_CYSCREEN);

	START_POSITION_X = (START_POSITION_X - SCREEN_SIZE_X)/2;
	START_POSITION_Y = (START_POSITION_Y - SCREEN_SIZE_Y)/2;

	m_Hwnd = CreateWindow(wcex.lpszClassName, 
		WINDOWS_TITLE, 
		WS_POPUPWINDOW,
		START_POSITION_X,		// 하기 4줄이 화면 시작 좌표 의미 
		START_POSITION_Y,		//
		SCREEN_SIZE_X,	// 1024 + 16
		SCREEN_SIZE_Y,	// 668 + 32
		NULL, 
		NULL, 
		wcex.hInstance, 
		NULL);

	if ( !m_Hwnd )
	{
		return S_FALSE;
	}

	ShowWindow(m_Hwnd, SW_SHOWNORMAL);
	SetForegroundWindow(m_Hwnd);		// Slightly Higher Priority
	SetFocus(m_Hwnd);					// Sets Keyboard Focus To The Window
	UpdateWindow(m_Hwnd);
	ShowCursor(false);

	return S_OK;
}

LRESULT CALLBACK CPKMainLoop::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch ( message )
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void CPKMainLoop::RunMessageLoop()
{
	MSG msg;
	HRESULT hr = S_FALSE;

	int	fps			= 0;
	DWORD prevTime	= timeGetTime();
	std::string fpsOldString = "FPS : 0";

	CPKRender::GetInstance()->Create();
	CPKRender::GetInstance()->InitOpenGL();

	CreateObject();

	while ( true )
	{
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			if ( msg.message == WM_QUIT )
			{
				return;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);	// Wndproc과 연결되어 있음
		}
		else
		{
			Sleep(1);
			DWORD nowTime = timeGetTime();

			std::string fpsNewString = "FPS : " + std::to_string(fps);

			CPKInputManager::GetInstance()->UpdateKeyState();
			
			// {} 로 스택을 활용하여 더미클래스의 생성자, 소멸자를 호출
			CPKDummyRender dummyRender;

			CPKLightManager::GetInstance()->SetLight();
				
			CPKObjectManager::GetInstance()->Update();
			CPKObjectManager::GetInstance()->Render();

			glPushMatrix();
			glRasterPos3f(-9.0f, 5.0f, -10.0f);
			
			for ( UINT i = 0 ; i < fpsOldString.length() ; ++i )
			{
				glColor3ub( 255, 255, 255 );
				glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24 , fpsOldString.c_str()[i] );
			}
			++fps;
			glPopMatrix();
			
			m_PrevTime = nowTime;

			if ( prevTime + 1000 < nowTime )
			{
				// printConsole( "FPS : %d   PT : %d   PN : %d \n" , fps, prevTime, nowTime );
				fpsOldString = fpsNewString;
				fps = 0;
				prevTime = nowTime;
			}
				
			if ( CPKInputManager::GetInstance()->GetKeyStatusByKey( KEY_TABLE_ESCAPE ) == KEY_STATUS_PRESSED )
			{
				return;
			}

			POINT	mousePoint;
			ZeroMemory(&mousePoint, sizeof(mousePoint));
			GetCursorPos( &mousePoint );

			CPKCameraManager::GetInstance()->SetFocus( mousePoint.x , mousePoint.y );
			// printConsole( "%d %d \n", mousePoint.x, mousePoint.y );
			SetCursorPos( SCREEN_SIZE_X / 2 , SCREEN_SIZE_Y / 2 );
		}
	}
}

void CPKMainLoop::CreateObject()
{
	CPKLightManager::GetInstance()->SetAmbient(0.1f, 0.1f, 0.1f, 1.0f);
	CPKLightManager::GetInstance()->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
	CPKLightManager::GetInstance()->SetSpecular(0.9f, 0.7f, 0.7f, 1.0f, 80);
	CPKLightManager::GetInstance()->SetSpecularRef(0.3f, 0.3f, 0.3f, 1.0f);
	CPKLightManager::GetInstance()->Init();
	CPKLightManager::GetInstance()->SetPosition(0, 0, -350.0f, 0);
	CPKLightManager::GetInstance()->SetPosition(0, 0, -650.0f, 1);
	CPKLightManager::GetInstance()->SetPosition(-150.0f, 0, -500.0f, 2);
	CPKLightManager::GetInstance()->SetPosition(150.0f, 0, -500.0f, 3);
	CPKLightManager::GetInstance()->SetPosition(0, -150.0f, -500.0f, 4);
	CPKLightManager::GetInstance()->SetPosition(0, 150.0f, -500.0f, 5);

	CPKTextureManager::GetInstance()->Init();

	// CPKChildBackground* bg = new CPKChildBackground();
	// CPKObjectManager::GetInstance()->AddObject(bg);

	CPKChildSphere* sun = new CPKChildSphere();
	sun->SetPosition(0, 0, -500.0f);
	sun->SetColor(240, 120, 40);
	sun->SetSize(50);
	sun->SetType(PLANET_TYPE_SUN);
	sun->SetSpin(0.01);
	CPKObjectManager::GetInstance()->AddObject(sun);

	CPKChildSphere* mercury = new CPKChildSphere();
	mercury->SetColor(160, 180, 150);
	mercury->SetSize(3);
	mercury->SetRadius(200);
	mercury->SetSpeed(0.113);
	mercury->SetParent(sun);
	mercury->SetGradient(3.38);
	mercury->SetType(PLANET_TYPE_MERCURY);
	mercury->SetSpin(3);
	CPKObjectManager::GetInstance()->AddObject(mercury);

	CPKChildSphere* venus = new CPKChildSphere();
	venus->SetColor(120, 150, 150);
	venus->SetSize(5);
	venus->SetRadius(280);
	venus->SetSpeed(0.044);
	venus->SetParent(sun);
	venus->SetGradient(3.86);
	venus->SetType(PLANET_TYPE_VENUS);
	venus->SetSpin(5);
	CPKObjectManager::GetInstance()->AddObject(venus);

	CPKChildSphere* earth = new CPKChildSphere();
	earth->SetColor(200, 200, 170);
	earth->SetSize(5);
	earth->SetRadius(350);
	earth->SetSpeed(0.027);
	earth->SetParent(sun);
	earth->SetGradient(7.25);
	earth->SetType(PLANET_TYPE_EARTH);
	earth->SetSpin(3);
	CPKObjectManager::GetInstance()->AddObject(earth);

	CPKChildSphere* moon = new CPKChildSphere();
	moon->SetColor(240, 200, 200);
	moon->SetSize(1);
	moon->SetRadius(12);
	moon->SetSpeed(0.366);
	moon->SetParent(earth);
	moon->SetGradient(5.14);
	moon->SetType(PLANET_TYPE_MOON);
	CPKObjectManager::GetInstance()->AddObject(moon);

	CPKChildSphere* mars = new CPKChildSphere();
	mars->SetColor(180, 120, 80);
	mars->SetSize(2);
	mars->SetRadius(420);
	mars->SetSpeed(0.014);
	mars->SetParent(sun);
	mars->SetGradient(5.65);
	mars->SetType(PLANET_TYPE_MARS);
	mars->SetSpin(3);
	CPKObjectManager::GetInstance()->AddObject(mars);

	CPKChildSphere* invisCenter = new CPKChildSphere();
	invisCenter->SetColor(2, 2, 2);
	invisCenter->SetSize(0.001);
	invisCenter->SetRadius(700);
	invisCenter->SetSpeed(0.007);
	invisCenter->SetParent(sun);
	invisCenter->SetGradient(3.27);
	CPKObjectManager::GetInstance()->AddObject(invisCenter);

	CPKChildSphere* doublePlanet_1 = new CPKChildSphere();
	doublePlanet_1->SetColor(240, 200, 200);
	doublePlanet_1->SetSize(1.7);
	doublePlanet_1->SetRadius(20.4);
	doublePlanet_1->SetSpeed(0.422);
	doublePlanet_1->SetParent(invisCenter);
	doublePlanet_1->SetGradient(3.32);
	doublePlanet_1->SetType(PLANET_TYPE_MOON);
	doublePlanet_1->SetSpin(0.5);
	CPKObjectManager::GetInstance()->AddObject(doublePlanet_1);

	CPKChildSphere* doublePlanet_2 = new CPKChildSphere();
	doublePlanet_2->SetColor(180, 200, 180);
	doublePlanet_2->SetSize(2.1);
	doublePlanet_2->SetRadius(14.3);
	doublePlanet_2->SetSpeed(0.422);
	doublePlanet_2->SetParent(invisCenter);
	doublePlanet_2->SetGradient(3.32);
	doublePlanet_2->SetType(PLANET_TYPE_VENUS);
	doublePlanet_2->SetSpin(0.7);
	CPKObjectManager::GetInstance()->AddObject(doublePlanet_2);
}
