#include "main.h"
#include "renderer.h"
#include "sprite.h"
#include "drawSprite.h"
#include "tool.h"

void Sprite::Init()
{
	GameObject::Init();

	transform->m_Position = Tool::ORIGIN;
	transform->m_Scale = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	m_drawSprite = AddComponent<DrawSprite>();
	m_drawSprite->SetMode(DrawSprite::DRAW_MODE::MODE_2D_EDIT);
	m_drawSprite->Load("asset/texture/white.png");
}