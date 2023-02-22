#pragma once
#include "scene.h"
#include <string>

class Manager
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	static Manager* GetInstance() {
		return s_pInstance;
	}

	static void Create()
	{
		if (!s_pInstance)
		{
			s_pInstance = new Manager();
		}
	}
	static void Destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	class Scene* GetScene(){ return m_Scene; }

	template <typename T>
	void SetScene()
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		m_Scene = new T();
		m_Scene->Init();
	}

	void SetScene(class Scene* next)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		m_Scene = next;
		m_Scene->Init();
	}

	bool GetExit() { return m_Exit; }
	void GameExit() { m_Exit = true; }

	const std::string tmpFileName = "scoretmp.txt";
	
private:
	Manager() : m_Exit(false) {}
	static class Scene* m_Scene;
	static Manager* s_pInstance;
	bool m_Exit;
};