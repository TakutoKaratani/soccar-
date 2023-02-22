#include "main.h"
#include "renderer.h"
#include "modelmanager.h"
#include "model.h"

ModelManager* ModelManager::s_pInstance = nullptr;

void ModelManager::Init()
{

}

void ModelManager::Uninit()
{
	std::unordered_map<const char*, Model*>::iterator iterator;
	
	for (iterator = m_pModels.begin(); iterator != m_pModels.end(); iterator++)
	{
		std::pair<const char*, Model*> model = *iterator;
		model.second->Unload();
		delete model.second;
	}
	m_pModels.clear();
}

Model* ModelManager::Load(const char* name)
{
	if (!m_pModels[name])
	{
		m_pModels[name] = new Model();
		m_pModels[name]->Load(name);
	}
	return m_pModels[name];
}