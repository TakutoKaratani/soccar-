#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "staminagauge.h"
#include "drawSprite.h"
#include "player.h"
#include "carcontrol.h"
#include "staminagaugeframe.h"

void StaminaGauge::Init()
{
	GameObject::Init();
	Player* p = Manager::GetInstance()->GetScene()->GetGameObject<Player>();
	m_cc = p->GetComponent<CarControl>();
	if (!m_cc) SetDestroy();

	float scale = 120.0f;

	transform->m_Position = D3DXVECTOR3(20.0f, SCREEN_HEIGHT - 20.0f, 0.0f);
	m_DefaultScale = D3DXVECTOR3(scale, scale * 3, 1.0f);
	transform->m_Scale = m_DefaultScale;

	m_GaugeSprite = AddComponent<DrawSprite>();
	m_GaugeSprite->SetMode(DrawSprite::DRAW_MODE::MODE_2D_EDIT_LEFTBOTTOM);
	m_GaugeSprite->Load("asset/texture/pixGauge.png");

	StaminaGaugeFrame* sgf = Manager::GetInstance()->GetScene()->AddGameObject<StaminaGaugeFrame>(3);
	sgf->SetPosition(transform->m_Position);
	sgf->SetScale(transform->m_Scale);
}

void StaminaGauge::Update()
{
	GameObject::Update();

	float staminaRatio = m_cc->GetStaminaRatio();

	SetScale(D3DXVECTOR3(m_DefaultScale.x, m_DefaultScale.y * staminaRatio, m_DefaultScale.z));
	m_GaugeSprite->SetUV(0.0f, 1.0f - staminaRatio, 1.0f, 1.0f);
}