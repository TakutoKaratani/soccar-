#pragma once
#include <list>
#include <typeinfo>
#include "component.h"
#include "transform.h"

class GameObject
{
protected:
	bool		m_Destroy = false;
	bool		m_DepthShadow = false;

	Transform* transform = nullptr;

	std::list<Component*> m_Component;
	float		m_distance = 0;
	int 		m_DestroyFrame = 0;
	int			m_Count = 0;

public:
	GameObject(){}
	virtual ~GameObject() {}

	template <typename T>
	T* AddComponent()
	{
		T* c = new T(this);
		c->Init();
		m_Component.push_back(c);

		return c;
	}

	template <typename T>
	T* GetComponent()
	{
		for (Component* c : m_Component)
		{
			if (typeid(*c) == typeid(T))
			{
				return (T*)c;
			}
		}
		return nullptr;
	}

	template <typename T>
	bool DestroyComponent()
	{
		for (Component* c : m_Component)
		{
			if (typeid(*c) == typeid(T))
			{
				c->SetDestroy();
				return true;
			}
		}
		return false;
	}

	virtual void Init() {
		transform = new Transform(this);
		transform->Init();
		for (Component* c : m_Component)
		{
			c->Init();
		}
	}
	virtual void Uninit() {
		for (Component* c : m_Component)
		{
			c->Uninit();
			delete c;
		}
		m_Component.clear();
		transform->Uninit();
		delete transform;
	}
	virtual void Update() {
		transform->Update();
		for (Component* c : m_Component)
		{
			c->Update();
		}
		m_Component.remove_if([](Component* component) {return component->Destroy(); });
		if (m_DestroyFrame != 0)
		{
			m_Count++;
			if (m_DestroyFrame <= m_Count)
			{
				m_Destroy = true;
			}
		}
	}
	virtual void Draw() {
		transform->Draw();
		for (Component* c : m_Component)
		{
			c->Draw();
		}
	}

	void SetDistnce(float dis) { m_distance = dis; }
	float GetDistance() const { return m_distance; }

	static bool comp (const GameObject* obj1,const GameObject* obj2){
		if (obj1->GetDistance() > obj2->GetDistance())
		{
			return true;
		}
		return false;
	}

	Transform* GetTransform() const { return transform; }
	void SetPosition(D3DXVECTOR3 pos) { transform->m_Position = pos; }
	D3DXVECTOR3 GetPosition() { return transform->m_Position; }
	void SetScale(D3DXVECTOR3 scl) { transform->m_Scale = scl; }
	D3DXVECTOR3 GetScale() { return transform->m_Scale; }
	void SetRotate(D3DXVECTOR3 rot) { transform->SerQuaternionRot(rot); }

	void MulQuaternion(D3DXQUATERNION q){ transform->MulQuaternion(q); }
	void MulQuaternion(D3DXVECTOR3 axis, float r) { transform->MulQuaternion(axis, r); }

	bool DepthShadow() { return m_DepthShadow; }

	void SetDestroy(int destroyframe = 0) { 
		if (destroyframe == 0)
		{
			m_Destroy = true;
		}
		else
		{
			m_DestroyFrame = destroyframe;
		}
	}

	/*
		11 12 13 14		11,12,13 X
		21 22 23 24		21,22,23 Y
		31 32 33 34		31,32,33 Z
		41 42 43 44
	*/

	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot,
			&transform->m_Quaternion);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot,
			&transform->m_Quaternion);

		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}

	D3DXVECTOR3 GetUp()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot,
			&transform->m_Quaternion);

		D3DXVECTOR3 up;
		up.x = rot._21;
		up.y = rot._22;
		up.z = rot._23;

		return up;
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

};
