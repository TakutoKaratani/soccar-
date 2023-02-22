#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "titlescene.h"
#include "tutorialscene.h"
#include "fade.h"

#include "input.h"

#include "sky.h"
#include "player.h"
#include "titlelogo.h"
#include "audio.h"
#include "titlemanager.h"
#include "titlecamera.h"
#include "playermoveComponent.h"
#include "simplerotation.h"
#include "whitecircle.h"
#include "drawmodel.h"
#include "light.h"

Audio* g_bgm;

void TitleScene::Init()
{
	m_MainCamera = AddGameObject<TitleCamera>(0);
	m_Light = AddGameObject<Light>(0);
	DrawModel* dm = AddGameObject<Sky>(0)->GetComponent<DrawModel>();
	dm->Load("asset\\model\\blacksky.obj");

	Player* player = AddGameObject<Player>(1);
	player->AddComponent<SimpleRotation>()->SetSpeed(0.01f);
	player->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 2.0f));
	player->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_Light->SetAt(player->GetPosition());
	m_Light->SetPosition(player->GetPosition() + D3DXVECTOR3(3.0f, 4.0f, 2.0f));

	WhiteCircle* wc = AddGameObject<WhiteCircle>(1);
	D3DXVECTOR3 playerPos = player->GetPosition();
	wc->SetPosition(D3DXVECTOR3(playerPos.x, -0.02f, playerPos.z - 0.1f));
	AddGameObject<TitleLogo>(2);
	m_titleManager = AddGameObject<TitleManager>(0);

	g_bgm = AddGameObject<Audio>(2);
	g_bgm->Load("asset\\sound\\chess.wav");
	g_bgm->SetVolume(0.0f);
	g_bgm->Play(true);
	g_bgm->FadeVolume(4.0f, 0.05f);
}

void TitleScene::Update()
{
	Scene::Update();
	if (m_titleManager->GetStart() && !Fade::GetInstance()->IsFade())
	{
		g_bgm->FadeStop(2.0f);
		Audio* jin = AddGameObject<Audio>(2);
		jin->Load("asset\\sound\\click.wav");
		jin->SetVolume(0.2f);
		jin->Play();
		Fade::GetInstance()->SetMode(Fade::FADE_MODE::MODE_ALPHA);
		Fade::GetInstance()->SetSpeed(0.6f);
		Fade::GetInstance()->FadeIn<TutorialScene>();
	}
}
