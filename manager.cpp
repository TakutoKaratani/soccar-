#include "main.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "scene.h"
#include "titlescene.h"
#include "modelmanager.h"
#include "texturemanager.h"
#include "gamescene.h"
#include "dioramascene.h"
#include "fade.h"
#include "audio.h"

Manager* Manager::s_pInstance = nullptr;
Scene* Manager::m_Scene = nullptr;

void Manager::Init()
{
	Renderer::GetInstance()->Init();
	Input::Init();
	Audio::InitMaster();

	ModelManager::Create();
	ModelManager::GetInstance()->Init();
	TextureManager::Create();
	TextureManager::GetInstance()->Init();

	Fade::Create();
	Fade::GetInstance()->Init();

	Fade::GetInstance()->SetMode(Fade::FADE_MODE::MODE_ALPHA);
	Fade::GetInstance()->SetSpeed(1.0f);
	Fade::GetInstance()->FadeOut<TitleScene>();
	//Fade::GetInstance()->FadeOut<DioramaScene>();

	m_Exit = false;
}


void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	Fade::GetInstance()->Uninit();
	Fade::Destroy();

	TextureManager::GetInstance()->Uninit();
	TextureManager::Destroy();
	ModelManager::GetInstance()->Uninit();
	ModelManager::Destroy();

	Audio::UninitMaster();
	Input::Uninit();
	Renderer::GetInstance()->Uninit();
}

void Manager::Update()
{
	Input::Update();
	Fade::GetInstance()->Update();
	m_Scene->Update();
}

void Manager::Draw()
{
	Renderer::GetInstance()->Begin();

	m_Scene->Draw();

	Fade::GetInstance()->Draw();

	Renderer::GetInstance()->End();

}
