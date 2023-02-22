#include "main.h"
#include "renderer.h"
#include "circleparticle.h"
#include "texturemanager.h"
#include "drawSprite.h"
#include "rigidbody.h"
#include "tool.h"

void CircleParticle::Init()
{
	GameObject::Init();
	transform->m_Position = Tool::ORIGIN;
	transform->SetScale(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	m_ds = AddComponent<DrawSprite>();
	m_ds->SetUV(0.0f, 0.0f, 1.0f, 1.0f);
	m_ds->SetMode(DrawSprite::DRAW_MODE::MODE_2D_EDIT);
	m_ds->Load("asset/texture/whitecircle.png");

	m_rb = AddComponent<Rigidbody>();
	m_rb->Gravity(false);
	m_rb->SetDrag(0.0f);
}