#include "main.h"
#include "manager.h"
#include "staminagaugeframe.h"
#include "DrawSprite.h"

void StaminaGaugeFrame::Init()
{
	GameObject::Init();

	float scale = 120.0f;

	transform->m_Position = D3DXVECTOR3(20.0f, SCREEN_HEIGHT - 20.0f, 0.0f);
	transform->m_Scale = D3DXVECTOR3(scale, scale * 3, 1.0f);

	DrawSprite* frame = AddComponent <DrawSprite>();
	frame->SetMode(DrawSprite::DRAW_MODE::MODE_2D_EDIT_LEFTBOTTOM);
	frame->Load("asset/texture/pixGaugeFrame.png");
}