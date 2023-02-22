#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texturemanager.h"
#include "fadebase.h"
#include "fadeCurtain.h"
#include "drawSprite.h"


void FadeCurtain::Init()
{
	GameObject::Init();

	m_DrawSprite = AddComponent<DrawSprite>();
	m_DrawSprite->Load("asset/texture/kao.png");
	m_DrawSprite->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_DrawSprite->SetMode(DrawSprite::DRAW_MODE::MODE_2D_EDIT_LEFTTOP);

	m_delay = 0.0f;
	transform->m_Position = D3DXVECTOR3(0.0f, -SCREEN_HEIGHT - m_delay, 0.0f);
	transform->m_Scale = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT + m_delay, 0.0f);
}

void FadeCurtain::Uninit()
{
	GameObject::Uninit();
}

void FadeCurtain::Update()
{
	GameObject::Update();
	switch (m_state)
	{
	case FADE_STATE::FADE_IN:
		transform->m_Position.y += m_Speed;
		if (transform->m_Position.y + transform->m_Scale.y > SCREEN_HEIGHT)
		{
			FadeOut();
		}
		break;
	case FADE_STATE::FADE_OUT:
		transform->m_Position.y -= m_Speed;
		if (transform->m_Position.y <= -SCREEN_HEIGHT - m_delay)
		{
			transform->m_Position.y = -SCREEN_HEIGHT - m_delay;
			m_state = FADE_STATE::FADE_NONE;
		}
		break;
	default:
		break;
	}
	
}

void FadeCurtain::Draw()
{
	GameObject::Draw();
}