#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "drawSprite.h"
#include "numbertext.h"

const D3DXVECTOR2* NumberText::m_ScoreNumSize = nullptr;
const D3DXCOLOR* NumberText::m_ScoreNumColor = nullptr;

void NumberText::Init()
{
	GameObject::Init();

	transform->m_Scale = D3DXVECTOR3(m_ScoreNumSize->x, m_ScoreNumSize->y, 0.0f);
	m_drawSprite = AddComponent<DrawSprite>();
	m_drawSprite->Load("asset/texture/number.png");
	m_drawSprite->SetColor(*m_ScoreNumColor);
	m_drawSprite->SetMode(DrawSprite::DRAW_MODE::MODE_2D_EDIT_LEFTTOP);
}

void NumberText::Uninit()
{
	GameObject::Uninit();
}

void NumberText::Update()
{
	GameObject::Update();
}

void NumberText::Draw()
{
	GameObject::Draw();
}

void NumberText::SetNumber(int num)
{

	m_drawSprite->SetUV(0.1f * num, 0.0f, 0.1f * num + 0.1f, 1.0f);
}
