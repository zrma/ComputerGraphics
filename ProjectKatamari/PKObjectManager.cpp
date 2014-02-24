#include "stdafx.h"
#include "PKMacro.h"
#include "PKObject.h"
#include "PKObjectManager.h"
#include "PKCameraManager.h"


CPKObjectManager::CPKObjectManager(void)
{
}


CPKObjectManager::~CPKObjectManager(void)
{
	for ( auto& iter : m_ObjectList )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectList.clear();
}

void CPKObjectManager::Update() const
{
	CPKCameraManager::GetInstance()->Update();

	for ( auto& iter : m_ObjectList )
	{
		iter->Update();
	}
}

void CPKObjectManager::Render() const
{
	for ( auto& iter : m_ObjectList )
	{
		iter->Render();
	}
}

void CPKObjectManager::AddObject( CPKObject* object )
{
	if (object != nullptr)
	{
		m_ObjectList.push_back(object);
	}
}
