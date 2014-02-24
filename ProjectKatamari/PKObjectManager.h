#pragma once

class CPKObject;
class CPKObjectManager
{
	SINGLETON(CPKObjectManager);
private:	
	CPKObjectManager(void);
	~CPKObjectManager(void);

public:
	void		Update() const;
	void		Render() const;

	void		AddObject(CPKObject* object);

private:
	std::list<CPKObject*>		m_ObjectList;
};

