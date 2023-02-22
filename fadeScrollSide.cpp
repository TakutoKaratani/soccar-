#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texturemanager.h"
#include "fadebase.h"
#include "fadeScrollSide.h"
#include "drawSprite.h"

void FadeScrollSide::Init()
{
	GameObject::Init();

	m_DrawSprite = AddComponent<DrawSprite>();
	m_DrawSprite->Load("asset/texture/kao.png");
	m_DrawSprite->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_DrawSprite->SetMode(DrawSprite::DRAW_MODE::MODE_2D_EDIT_LEFTTOP);

	m_delay = 100.0f;
	transform->m_Position = D3DXVECTOR3(SCREEN_WIDTH , 0.0f, 0.0f);
	transform->m_Scale = D3DXVECTOR3(SCREEN_WIDTH + m_delay, SCREEN_HEIGHT, 0.0f);
}

void FadeScrollSide::Uninit()
{
	GameObject::Uninit();
}

void FadeScrollSide::Update()
{
	GameObject::Update();
	switch (m_state)
	{
	case FADE_STATE::FADE_IN:
		transform->m_Position.x -= m_Speed;
		if (transform->m_Position.x <= 0.0f - m_delay * 0.5f)
		{
			FadeOut();
		}
		break;
	case FADE_STATE::FADE_OUT:
		transform->m_Position.x -= m_Speed;
		if (transform->m_Position.x <= -SCREEN_WIDTH - m_delay)
		{
			transform->m_Position.x = -SCREEN_WIDTH - m_delay;
			m_state = FADE_STATE::FADE_NONE;
		}
		break;
	default:
		break;
	}
}

void FadeScrollSide::Draw()
{
	GameObject::Draw();
}