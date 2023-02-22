#pragma once

class Component
{
public:
	Component(class GameObject* go):gameObject(go){}
	virtual ~Component(){}

	virtual void Init() {}
	virtual void Uninit() {}
	virtual void Update() {}
	virtual void Draw() {}

	void SetDestroy()
	{
		m_Destroy = true;
	}

	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	class GameObject* gameObject = nullptr;

private:
	Component(){}

protected:
	bool	m_Destroy = false;
};
