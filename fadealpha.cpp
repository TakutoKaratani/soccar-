#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texturemanager.h"
#include "fadebase.h"
#include "fadealpha.h"
#include "drawSprite.h"

void FadeAlpha::Init()
{
	GameObject::Init();

	transform->m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	transform->m_Scale = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	m_DrawSprite = AddComponent<DrawSprite>();
	m_DrawSprite->Load("asset/texture/white.png");
	m_DrawSprite->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_DrawSprite->SetMode(DrawSprite::DRAW_MODE::MODE_2D_EDIT_LEFTTOP);
}

void FadeAlpha::Uninit()
{
	GameObject::Uninit();
}

void FadeAlpha::Update()
{
	GameObject::Update();
	switch (m_state)
	{
	case FADE_STATE::FADE_IN:
		m_alpha += m_Speed;
		if (m_alpha >= 1.0f)
		{
			FadeOut();
		}
		break;
	case FADE_STATE::FADE_OUT:
		m_alpha -= m_Speed;
		if (m_alpha <= 0.0f)
		{
			m_alpha = 0;
			m_state = FADE_STATE::FADE_NONE;
		}
		break;
	default:
		break;
	}
	D3DXCOLOR c = m_DrawSprite->GetColor();
	c.a = m_alpha;
	m_DrawSprite->SetColor(c);
}

void FadeAlpha::Draw()
{
	GameObject::Draw();
}