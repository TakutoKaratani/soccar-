#include "main.h"
#include "manager.h"
#include "resultmanager.h"
#include "input.h"

#include "player.h"
#include "enemy.h"
#include "soccergoal.h"
#include "number.h"
#include "sprite.h"
#include "drawSprite.h"
#include "tool.h"

#include<iostream>
#include<fstream>

void ResultManager::Init()
{
	GameObject::Init();
	LoadScore();

	changeScene = false;

	Scene* scene = Manager::GetInstance()->GetScene();
	Camera* camera = scene->GetMainCamera();

	Sprite* bo = scene->AddGameObject<Sprite>(2);
	bo->SetPosition(Tool::ORIGIN);
	bo->SetScale(D3DXVECTOR3(100.0f, 25.0f, 1.0f));

	Sprite* text = scene->AddGameObject<Sprite>(3);
	DrawSprite* textds = text->GetDrawSprite();
	textds->Load("asset/texture/resulttext.png");
	float textsize = 450.0f;
	text->SetScale(D3DXVECTOR3(textsize, textsize * 0.8f * 0.33f, 1.0f));
	text->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.2f, 0.0f));

	Number* score[2] = { scene->AddGameObject<Number>(3),scene->AddGameObject<Number>(3) };
	D3DXVECTOR3 scoresize = { 200.0f,200.0f,1.0f };
	for (int i = 0; i < 2; i++)
	{
		score[i]->SetNumber(m_Point[i]);
		score[i]->SetScale(scoresize);
		score[i]->SetInterval(scoresize.x * 0.75f);
	}

	if (m_Point[0] > m_Point[1])
	{
		score[1]->SetScale(scoresize * 0.6f);
		score[1]->SetInterval(scoresize.x * 0.6f * 0.75f);
		textds->SetUV(0.0f, 0.0f, 1.0f, 0.33f);
		textds->SetColor(D3DXCOLOR(0.9f, 0.0f, 0.0f, 1.0f));
	}
	else if (m_Point[0] < m_Point[1])
	{
		score[0]->SetScale(scoresize * 0.6f);
		score[0]->SetInterval(scoresize.x * 0.6f * 0.75f);
		textds->SetUV(0.0f, 0.33f, 1.0f, 0.66f);
		textds->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.9f, 1.0f));
	}
	else
	{
		textds->SetUV(0.0f, 0.66f, 1.0f, 1.0f);
	}
	score[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.33f, SCREEN_HEIGHT * 0.5f, 1.0f));
	score[0]->SetMode(Number::MODE::RIGHT);



	score[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.66f, SCREEN_HEIGHT * 0.5f, 1.0f));
	score[1]->SetMode(Number::MODE::LEFT);

	camera->SetPosition(D3DXVECTOR3(0.0, 4.0f, -0.0f));
	camera->SetTargetPos(D3DXVECTOR3(0.0f, 0.0f, -40.0f));

	Player* player = scene->AddGameObject<Player>(1);
	player->SetPosition(D3DXVECTOR3(7.0f, 0.0, -10.0f));
	player->SetRotate(D3DXVECTOR3(0.0f, Tool::PI * -0.3f, 0.0f));

	Enemy* enemy = scene->AddGameObject<Enemy>(1);
	enemy->SetPosition(D3DXVECTOR3(-7.0f, 0.0, -10.0f));
	enemy->SetRotate(D3DXVECTOR3(0.0f, Tool::PI * 0.3f, 0.0f));

	SoccerGoal* goal = scene->AddGameObject<SoccerGoal>(1);
	goal->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -45.0f));


	Light* light = Manager::GetInstance()->GetScene()->GetLight();
	if (light)
	{
		light->SetPosition(D3DXVECTOR3(-6.0f, 7.0f, -1.0f));
		light->SetAt(D3DXVECTOR3(1.5f, 2.0f, -12.0f));
	}

}

void ResultManager::Uninit()
{
	GameObject::Uninit();
}

void ResultManager::Update()
{
	GameObject::Update();

	if (Input::GetKeyTrigger(VK_LBUTTON))
	{
		changeScene = true;
	}
}

void ResultManager::LoadScore()
{
	std::ifstream readfile;
	readfile.open(Manager::GetInstance()->tmpFileName);
	std::string buff;

	int i = 0;
	while (std::getline(readfile, buff))
	{
		m_Point[i] = stoi(buff);
		i++;
		if (i > 1) break;
	}
}