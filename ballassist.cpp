#include "main.h"
#include "manager.h"
#include "ball.h"
#include "ballassist.h"
#include "drawSprite.h"
#include "tool.h"

void BallAssist::Init()
{
	GameObject::Init();
	m_ds = AddComponent<DrawSprite>();
	m_ds->Load("asset/texture/ballassist.png");
	m_ds->SetMode(DrawSprite::DRAW_MODE::MODE_3D_EDIT);

	transform->SerQuaternionRot(D3DXVECTOR3(Tool::PI * 0.5f, 0.0f, 0.0f));
	transform->SetScale(D3DXVECTOR3(3.0f, 3.0f, 1.0f));

	color = { 1.0f,1.0f,1.0f,0.0f };

	m_ds->SetColor(color);

	ball = Manager::GetInstance()->GetScene()->GetGameObject<Ball>();
	if (!ball) SetDestroy();
}

void BallAssist::Update()
{
	GameObject::Update();

	D3DXVECTOR3 pos = ball->GetPosition();
	pos.y = 0.1f;
	SetPosition(pos);


	float len = ball->GetPosition().y - (ball->GetScale().y * 0.5f);

	float showdis = 15.0f;

	float ratio = showdis - len;

	if (ratio < 0) color.a = 1.0f;
	else
	{
		color.a = 1.0f - (ratio / showdis);
	}
	m_ds->SetColor(color);
}