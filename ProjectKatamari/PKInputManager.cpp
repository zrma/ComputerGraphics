#include "stdafx.h"
#include "PKMacro.h"
#include "PKInputManager.h"


CPKInputManager::CPKInputManager(void)
{
}


CPKInputManager::~CPKInputManager(void)
{
}

void CPKInputManager::UpdateKeyState()
{
	for ( int i = 0 ; i < MAX_INPUT_KEY ; i++ )
	{
		m_PrevKeyState[i] = m_NowKeyState[i];

		if( GetAsyncKeyState( i ) & 0x8000 )
		{
			m_NowKeyState[i] = true;
		}
		else
		{
			m_NowKeyState[i] = false;
		}
	}
}

KeyStatus CPKInputManager::GetKeyStatusByKey( KeyTable key ) const
{
	if ( GetActiveWindow() == NULL )
	{
		return KEY_STATUS_NOT_PRESSED;
	}
	if ( m_PrevKeyState[key] == false && m_NowKeyState[key] == true )
	{
		return KEY_STATUS_DOWN;
	}
	else if ( m_PrevKeyState[key] == true && m_NowKeyState[key] == true )
	{
		return KEY_STATUS_PRESSED;
	}
	else if ( m_PrevKeyState[key] == true && m_NowKeyState[key] == false )
	{
		return KEY_STATUS_UP;
	}

	return KEY_STATUS_NOT_PRESSED;
}

void CPKInputManager::SetKeyStatusByKey( KeyTable key , KeyStatus keyStatus )
{
	if ( keyStatus == KEY_STATUS_DOWN )
	{
		m_PrevKeyState[key] = false;
		m_NowKeyState[key] = true;
	}
	else if ( keyStatus == KEY_STATUS_PRESSED )
	{
		m_PrevKeyState[key] = true;
		m_NowKeyState[key] = true;
	}
	else if ( keyStatus == KEY_STATUS_UP )
	{
		m_PrevKeyState[key] = true;
		m_NowKeyState[key] = false;
	}
}
