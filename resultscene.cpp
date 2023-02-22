#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "resultscene.h"
#include "titlescene.h"
#include "fade.h"

#include "audio.h"
#include "titlecamera.h"
#include "Light.h"
#include "sky.h"
#include "Field.h"
#include "resultmanager.h"

Audio* g_resultbgm = nullptr;

void ResultScene::Init()
{
	m_MainCamera = AddGameObject<TitleCamera>(0);
	m_Light = AddGameObject<Light>(0);
	AddGameObject<Sky>(0);
	AddGameObject<Field>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_ResultManager = AddGameObject<ResultManager>(0);
	g_resultbgm = AddGameObject<Audio>(2);
	g_resultbgm->Load("asset\\sound\\bgm_sizen.wav");
	g_resultbgm->Play(true);
	g_resultbgm->FadeVolume(4.0f, 0.7f);
}

void ResultScene::Update()
{
	Scene::Update();

	if (m_ResultManager->ChangeScene() && !Fade::GetInstance()->IsFade())
	{
		g_resultbgm->FadeStop(2.0f);
		Fade::GetInstance()->SetMode(Fade::FADE_MODE::MODE_ALPHA);
		Fade::GetInstance()->SetSpeed(0.6f);
		Fade::GetInstance()->FadeIn<TitleScene>();
	}
}