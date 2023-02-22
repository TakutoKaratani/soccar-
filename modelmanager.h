#pragma once
#include <string>
#include <unordered_map>

class Model;

class ModelManager
{
public:
	void Init();
	void Uninit();

	Model* Load(const char*);

	static ModelManager* GetInstance() {
		return s_pInstance;
	}

	static void Create()
	{
		if (!s_pInstance)
		{
			s_pInstance = new ModelManager();
		}
	}
	static void Destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

private:
	static ModelManager* s_pInstance;

	std::unordered_map<const char*, Model*> m_pModels;
};
