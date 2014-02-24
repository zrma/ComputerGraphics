#pragma once
#include "PKKeyMapping.h"
#include "PKEnumSet.h"
#include "PKDefine.h"

class CPKInputManager
{
	SINGLETON(CPKInputManager);
private:
	CPKInputManager(void);
	~CPKInputManager(void);

public:
	void				UpdateKeyState();
	KeyStatus			GetKeyStatusByKey( KeyTable key ) const;
	void				SetKeyStatusByKey( KeyTable key , KeyStatus keyStatus );

private:
	std::array<KeyStatus, MAX_INPUT_KEY>	m_InputKey;

	std::array<bool, MAX_INPUT_KEY>			m_PrevKeyState;
	std::array<bool, MAX_INPUT_KEY>			m_NowKeyState;
};

