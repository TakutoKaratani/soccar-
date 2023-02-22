#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "gamescene.h"
#include "resultscene.h"
#include "input.h"
#include "fade.h"
#include "gamemanager.h"
#include "Field.h"
#include "gamecamera.h"
#include "sky.h"
#include "audio.h"
#include "drawSprite.h"
#include "gamelight.h"
#include "tool.h"

DrawSprite* ds;

void GameScene::Init()
{
	m_MainCamera = AddGameObject<GameCamera>(0);
	m_Light = AddGameObject<GameLight>(0);
	AddGameObject<Sky>(0);
	AddGameObject<Field>(0)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	m_GM = AddGameObject<GameManager>(0);
	Audio * g = AddGameObject<Audio>(2);
	g->Load("asset\\sound\\bgm_sizen.wav");
	g->Play(true);
	g->FadeVolume(4.0f, 0.7f);
}

void GameScene::Uninit()
{
	Scene::Uninit();
}

void GameScene::Update()
{
	Scene::Update();

	if (m_GM->ChangeResult() && !Fade::GetInstance()->IsFade())
	{
		Fade::GetInstance()->SetMode(Fade::FADE_MODE::MODE_ALPHA);
		Fade::GetInstance()->SetSpeed(0.6f);
		Fade::GetInstance()->FadeIn<ResultScene>();
	}
}