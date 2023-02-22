#include "main.h"
#include "manager.h"
#include "ball.h"
#include "wall.h"
#include "drawSprite.h"
#include "tool.h"

void Wall::Init()
{
	GameObject::Init();
	m_ds = AddComponent<DrawSprite>();
	m_ds->Load("asset/texture/whitecircle.png");
	m_ds->SetMode(DrawSprite::DRAW_MODE::MODE_3D_EDIT);

	transform->SetScale(D3DXVECTOR3(5.0f, 5.0f, 5.0f));

	setPos = new Wall::SetPosX();

	color = { 1.0f,1.0f,1.0f,0.0f };

	m_ds->SetColor(color);

	ball = Manager::GetInstance()->GetScene()->GetGameObject<Ball>();
	if (!ball) SetDestroy();
}

void Wall::Uninit()
{
	GameObject::Uninit();
	delete setPos;
}

void Wall::Update()
{
	GameObject::Update();
	setPos->Update(this);

	float len = Tool::Vec3Length(GetPosition() - ball->GetPosition());

	float showdis = 20.0f;

	float ratio = showdis - len;

	if (ratio < 0) color.a = 0;
	else
	{
		ratio /= showdis;
		color.a = ratio;
	}
	m_ds->SetColor(color);
}


void Wall::SetPosX::Update(Wall* wall)
{
	D3DXVECTOR3 pos = wall->ball->GetPosition();
	pos.z = wall->GetPosition().z;
	wall->SetPosition(pos);
}

void Wall::SetPosZ::Update(Wall* wall)
{
	D3DXVECTOR3 pos = wall->ball->GetPosition();
	pos.x = wall->GetPosition().x;
	wall->SetPosition(pos);
}