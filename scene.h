#pragma once
#include <list>
#include <vector>
#include <typeinfo>
#include "camera.h"
#include "gameObject.h"
#include "renderer.h"
#include "light.h"

class Scene
{
protected:
	std::list<GameObject*> m_GameObject[4];
	/*
		0:
		1:3D空間オブジェクト
		2:UI
		3:最前面UI
	*/
	Camera* m_MainCamera = nullptr;
	Light* m_Light = nullptr;
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() = 0;

	Camera* GetMainCamera() { return m_MainCamera; }
	Light* GetLight() { return m_Light; }

	template <typename T>
	T* AddGameObject(int layer)
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject[layer].push_back(gameObject);

		return gameObject;
	}

	template <typename T>
	T* GetGameObject()
	{
		for (int i = 0; i < 4; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))
				{
					return (T*)object;
				}
			}
		}
		return nullptr;
	}

	template <typename T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objects;
		for (int i = 0; i < 4; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))
				{
					objects.push_back((T*)object);
				}
			}
		}
		return objects;
	}

	virtual void Uninit()
	{
		for (int i = 0; i < 4; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < 4; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Update();
			}
			m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });
		}

		if (m_MainCamera)
		{
			for (GameObject* object : m_GameObject[1])
			{
				D3DXVECTOR3 direction = object->GetPosition() - m_MainCamera->GetPosition();
				float length = D3DXVec3Length(&direction);
				object->SetDistnce(length);
			}
			m_GameObject[1].sort(GameObject::comp);

			Renderer::GetInstance()->SetCameraPosition(m_MainCamera->GetPosition());
		}
	}

	virtual void Draw()
	{
		if (m_Light)
		{
			m_Light->SetLight();
			Renderer::GetInstance()->BeginDepth();

			for (GameObject* object : m_GameObject[1])
			{
				if (object->DepthShadow())
					object->Draw();
			}
		}

		Renderer::GetInstance()->Begin();

		for (int i = 0; i < 4; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

};
