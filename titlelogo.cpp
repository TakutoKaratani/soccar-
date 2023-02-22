#include "main.h"
#include "renderer.h"
#include "titlelogo.h"
#include "texturemanager.h"
#include "drawSprite.h"
#include "tool.h"

void TitleLogo::Init()
{
	GameObject::Init();

	transform->m_Position = Tool::ORIGIN + D3DXVECTOR3(0.0f, -170.0f, 0.0f);
	transform->m_Scale = D3DXVECTOR3(600.0f, 100.0f, 0.0f);
	m_ds = AddComponent<DrawSprite>();
	m_ds->SetUV(0.0f, 0.0f, 1.0f, 1.0f);
	m_ds->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_ds->SetMode(DrawSprite::DRAW_MODE::MODE_2D);
	m_ds->Load("asset/texture/soccarlogo.png");
	m_ds->SubTextureLoad("asset/texture/car.png");

	m_ds->SetShader("innerTextureVS.cso", "innerTexturePS.cso");

	u = 0.0f;
}

void TitleLogo::Uninit()
{
	GameObject::Uninit();
}

void TitleLogo::Update()
{
	GameObject::Update();

	u += 0.003f;
	if (u >= 1) u = 0;

	m_ds->SetParameter(D3DXVECTOR4(u, 0.0f, 0.0f, 0.0f));
}

void TitleLogo::Draw()
{
	GameObject::Draw();
}