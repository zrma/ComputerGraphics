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
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	// ��ü ���̵� ��� �����ϵ��� static���� ��
	
	HWND					m_Hwnd;
	DWORD					m_PrevTime;
};

