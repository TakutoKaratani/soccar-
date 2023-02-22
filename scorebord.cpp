#include "main.h"
#include "manager.h"
#include "scorebord.h"
#include "renderer.h"
#include "drawSprite.h"
#include "gamemanager.h"
#include "number.h"
#include "sprite.h"

void ScoreBord::Init()
{
	GameObject::Init();

	transform->SetScale(D3DXVECTOR3(400.0f, 100.0f,1.0f));
	transform->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, GetScale().y * 0.5f, 0.0f));

	DrawSprite* ds = AddComponent<DrawSprite>();
	ds->Load("asset/texture/scorebord.png");
	ds->SetMode(DrawSprite::DRAW_MODE::MODE_2D);


	Scene* scene = Manager::GetInstance()->GetScene();

	D3DXVECTOR3 offset = { GetScale().x * 0.35f,0.0f,0.0f };
	D3DXVECTOR3 scoresize = { GetScale().y * 0.45f,GetScale().y * 0.45f,1.0f };

	for (int i = 0; i < 2; i++)
	{
		m_Score[i] = scene->AddGameObject<Number>(3);
		m_Score[i]->SetScale(scoresize);
		m_Score[i]->SetInterval(scoresize.x * 0.75f);
		m_Score[i]->SetNumber(0);
		m_Score[i]->ZeroCover(false);
		m_Score[i]->SetMaxNum(99);
	}
	m_Score[0]->SetPosition(GetPosition() - offset);
	m_Score[0]->SetMode(Number::MODE::RIGHT);

	m_Score[1]->SetPosition(GetPosition() + offset);
	m_Score[1]->SetMode(Number::MODE::LEFT);


	offset = { GetScale().x * -0.08f, GetScale().y * 0.08f,0.0f};

	D3DXVECTOR3 timersize = { GetScale().y * 0.55f,GetScale().y * 0.55f,1.0f };

	m_Min = scene->AddGameObject<Number>(3);
	m_Min->SetScale(timersize);
	m_Min->SetInterval(timersize.x * 0.8f);
	m_Min->SetNumber(0);
	m_Min->SetMode(Number::MODE::RIGHT);
	m_Min->SetPosition(GetPosition() + offset);
	m_Min->SetMaxNum(99);

	offset.x *= -1;

	m_Sec = scene->AddGameObject<Number>(3);
	m_Sec->SetScale(timersize);
	m_Sec->SetInterval(timersize.x * 0.8f);
	m_Sec->SetNumber(0);
	m_Sec->ZeroCover(true);
	m_Sec->SetMode(Number::MODE::LEFT);
	m_Sec->SetPosition(GetPosition() + offset);
	m_Sec->SetMaxNum(60);

	offset.x = 0;

	Sprite* colon = scene->AddGameObject<Sprite>(3);
	colon->SetPosition(GetPosition() + offset);
	colon->SetScale(timersize);
	colon->GetDrawSprite()->Load("asset/texture/colon.png");
}

void ScoreBord::Update()
{
	GameObject::Update();
}

void ScoreBord::SetScore(int i, int score)
{
	if (i < 0) i = 0;
	if (i > 1)i = 1;

	m_Score[i]->SetNumber(score);
}

void ScoreBord::SetTime(int min, int sec)
{
	m_Min->SetNumber(min);
	m_Sec->SetNumber(sec);
}