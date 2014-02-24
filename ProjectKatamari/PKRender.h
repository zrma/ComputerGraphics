#pragma once
class CPKRender
{
	SINGLETON(CPKRender);
private:
	CPKRender(void);
	~CPKRender(void);

public:
	void	Create();
	void	Release();

	void	InitOpenGL();
	void	RenderBegin();
	void	RenderEnd();

	BOOL	SetPixelFormatRender(HDC hdc);

private:
	HDC		m_hDC;		// GDI Device Context
	HGLRC	m_hglRC;	// Rendering  Context
};