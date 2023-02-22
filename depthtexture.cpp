#include "main.h"
#include "renderer.h"
#include "depthtexture.h"
#include "drawSprite.h"

void DepthTexture::Init()
{
	GameObject::Init();
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetScale(D3DXVECTOR3((float)SCREEN_WIDTH * 0.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f));
	m_ds = AddComponent<DrawSprite>();
	m_ds->SetMode(DrawSprite::DRAW_MODE::MODE_2D_EDIT_LEFTTOP);
	m_ds->SetTexture(Renderer::GetInstance()->GetShadowDepthTexture());
}

void DepthTexture::Update()
{
	m_ds->SetTexture(Renderer::GetInstance()->GetShadowDepthTexture());
}
