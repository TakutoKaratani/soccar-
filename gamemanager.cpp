#include "main.h"
#include "manager.h"
#include "gamemanager.h"
#include "tool.h"

#include "player.h"
#include "enemy.h"
#include "ball.h"
#include "soccergoal.h"
#include "staminagauge.h"
#include "scorebord.h"
#include "number.h"
#include "timer.h"
#include "playermoveComponent.h"
#include "rigidbody.h"
#include "wall.h"
#include "sprite.h"
#include "drawSprite.h"
#include "ballassist.h"
#include "audio.h"

#include<iostream>
#include<fstream>

static const float gameTime = 90.0f;

void GameManager::Init()
{
	GameObject::Init();
	Scene* scene = Manager::GetInstance()->GetScene();

	m_Player = scene->AddGameObject<Player>(1);
	m_Enemy = scene->AddGameObject<Enemy>(1);
	m_Ball = scene->AddGameObject<Ball>(1);

	scene->AddGameObject<BallAssist>(1);


	m_Goal[0] = scene->AddGameObject<SoccerGoal>(1);
	m_Goal[0]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 200.0f));
	m_Goal[0]->SetRotate(D3DXVECTOR3(0.0f, Tool::PI, 0.0f));
	Sprite* bar = scene->AddGameObject<Sprite>(1);
	bar->SetPosition(D3DXVECTOR3(0.0f, 20.0f, 200.0f));
	bar->SetScale(D3DXVECTOR3(13.0f, 1.0f,1.0f));
	DrawSprite* ds = bar->GetDrawSprite();
	ds->SetColor(D3DXCOLOR(0.9f, 0.0f, 0.0f, 1.0f));
	ds->SetMode(DrawSprite::DRAW_MODE::MODE_3D_BILLBOARD_EDIT);
	m_Point[0] = 0;

	m_Goal[1] = scene->AddGameObject<SoccerGoal>(1);
	m_Goal[1]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -200.0f));
	bar = scene->AddGameObject<Sprite>(1);
	bar->SetPosition(D3DXVECTOR3(0.0f, 20.0f, -200.0f));
	bar->SetScale(D3DXVECTOR3(13.0f, 1.0f, 1.0f));
	ds = bar->GetDrawSprite();
	ds->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.9f, 1.0f));
	ds->SetMode(DrawSprite::DRAW_MODE::MODE_3D_BILLBOARD_EDIT);
	m_Point[1] = 0;

	Wall* wall = scene->AddGameObject<Wall>(1);
	wall->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 210.0f));

	wall = scene->AddGameObject<Wall>(1);
	wall->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -210.0f));
	wall->SetRotate(D3DXVECTOR3(0.0f, Tool::PI, 0.0f));


	wall = scene->AddGameObject<Wall>(1);
	wall->SetPosition(D3DXVECTOR3(100.0f, 0.0f, 0.0f));
	wall->SetRotate(D3DXVECTOR3(0.0f, Tool::PI * 0.5f, 0.0f));
	wall->Z();


	wall = scene->AddGameObject<Wall>(1);
	wall->SetPosition(D3DXVECTOR3(-100.0f, 0.0f, 0.0f));
	wall->SetRotate(D3DXVECTOR3(0.0f, -Tool::PI * 0.5f, 0.0f));
	wall->Z();

	m_ScoreBord = scene->AddGameObject<ScoreBord>(2);

	timer = scene->AddGameObject<Timer>(0);
	timer->SetTime(gameTime);

	scene->AddGameObject<StaminaGauge>(3);

	m_SE[0] = scene->AddGameObject<Audio>(0);
	m_SE[0]->Load("asset\\sound\\whistle1.wav");
	m_SE[0]->SetVolume(0.2f);
	m_SE[1] = scene->AddGameObject<Audio>(0);
	m_SE[1]->Load("asset\\sound\\whistle2.wav");
	m_SE[1]->SetVolume(0.2f);

	Reset();

	gUpdate = new GameManager::GameUpdateStart();

	m_StopGame = false;
}

void GameManager::Uninit()
{
	GameObject::Uninit();
	delete gUpdate;
}

void GameManager::Update()
{
	GameObject::Update();

	gUpdate->Update(this);

	float time = timer->GetTime();
	int min, sec;
	min = (int)time / 60;
	sec = (int)time % 60;

	m_ScoreBord->SetTime(min, sec);
}

void GameManager::Reset()
{
	D3DXVECTOR3 playerPos(0.0f, 0.0f, -50.0f);

	m_Player->SetPosition(playerPos);
	m_Player->SetRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Enemy->SetPosition(-playerPos);
	m_Enemy->SetRotate(D3DXVECTOR3(0.0f, Tool::PI, 0.0f));

	m_Ball->GetComponent<Rigidbody>()->velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR2 rand = Tool::RandVec2D(8, 0);
	rand *= 8.0f;

	m_Ball->SetPosition(D3DXVECTOR3(rand.x, 0.0f, rand.y));
	m_Goal[0]->Reset();
	m_Goal[1]->Reset();
}



void GameManager::GameUpdate::Update(GameManager* gm)
{
	bool goal = false;
	for (int i = 0; i < 2; i++)
	{
		if (gm->m_Goal[i]->Goal())
		{
			gm->m_Point[i]++;
			gm->m_ScoreBord->SetScore(i, gm->m_Point[i]);
			goal = true;
			gm->timer->Stop();
		}
	}

	if (goal)
	{
		gm->m_SE[1]->Play();
		delete gm->gUpdate;
		gm->gUpdate = new GameManager::GameUpdateGoal();
	}
	else if (gm->timer->GetTime() <= 0)
	{
		gm->m_SE[0]->Play();
		delete gm->gUpdate;
		gm->gUpdate = new GameManager::GameUpdateFinish();
	}
}



GameManager::GameUpdateGoal::GameUpdateGoal()
{
	resetTimer = Manager::GetInstance()->GetScene()->AddGameObject<Timer>(0);
	resetTime = 3.5f;
	resetTimer->SetTime(resetTime);
	resetTimer->Start();
}

void GameManager::GameUpdateGoal::Update(GameManager* gm)
{
	if (resetTimer->GetTime() <= 0)
	{
		if (gm->m_Player->GetComponent<PlayermoveComponent>())
		{
			gm->m_Player->GetComponent<PlayermoveComponent>()->SetDestroy();
		}
		gm->m_Player->GetComponent<Rigidbody>()->constraints.FreezeAll();
		gm->Reset();
		gm->m_Enemy->AIStop();
		gm->m_Enemy->GetComponent<Rigidbody>()->constraints.FreezeAll();
		resetTimer->SetDestroy();
		delete gm->gUpdate;
		gm->gUpdate = new GameManager::GameUpdateStart();
	}
}

GameManager::GameUpdateStart::GameUpdateStart()
{
	startTimer = Manager::GetInstance()->GetScene()->AddGameObject<Timer>(0);
	startTime = 3.0f;
	startTimer->SetTime(startTime);
	startTimer->Start();

	countSprite = Manager::GetInstance()->GetScene()->AddGameObject<Number>(3);
	countSprite->SetPosition(Tool::ORIGIN);
	countSprite->SetScale(D3DXVECTOR3(250.f, 250.f, 1.0f));
	countSprite->SetNumber((int)startTimer->GetTime() + 1);
}

void GameManager::GameUpdateStart::Update(GameManager* gm)
{
	countSprite->SetNumber((int)startTimer->GetTime() + 1);

	if (startTimer->GetTime() <= 0)
	{
		gm->m_Player->AddComponent<PlayermoveComponent>();
		gm->m_Player->GetComponent<Rigidbody>()->constraints.DefrostAll();
		gm->m_Enemy->AIStart();
		gm->m_Enemy->GetComponent<Rigidbody>()->constraints.DefrostAll();
		gm->timer->Start();
		countSprite->SetDestroy();
		startTimer->SetDestroy();
		gm->m_SE[0]->Play();
		delete gm->gUpdate;
		gm->gUpdate = new GameManager::GameUpdate();
	}
}


GameManager::GameUpdateFinish::GameUpdateFinish()
{
	finishTimer = Manager::GetInstance()->GetScene()->AddGameObject<Timer>(0);
	finishTime = 3.0f;
	finishTimer->SetTime(finishTime);
	finishTimer->Start();
	Sprite* gametext = Manager::GetInstance()->GetScene()->AddGameObject<Sprite>(3);
	float size = 500.0f;
	gametext->SetScale(D3DXVECTOR3(size, size * 0.3f, 1.0f));
	gametext->GetDrawSprite()->Load("asset/texture/game!.png");
}

void GameManager::GameUpdateFinish::Update(GameManager* gm)
{
	if (finishTimer->GetTime() <= 0)
	{
		gm->m_ChangeScene = true;

		std::ofstream outputfile(Manager::GetInstance()->tmpFileName);
		outputfile << gm->m_Point[0] << "\n" << gm->m_Point[1];
		outputfile.close();
	}
}

