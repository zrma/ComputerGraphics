#pragma once

class CPKMainLoop
{
public:
	SINGLETON(CPKMainLoop);
private:
	CPKMainLoop(void);
	~CPKMainLoop(void);

public:
	HRESULT					CreateMainLoopWindow();
	void					RunMessageLoop();

	void					CreateObject();

	HWND					GetHwnd() { return m_Hwnd; }

private:
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	// 객체 없이도 사용 가능하도록 static으로 함
	
	HWND					m_Hwnd;
	DWORD					m_PrevTime;
};

