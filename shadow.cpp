#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texturemanager.h"
#include "shadow.h"
#include "drawSprite.h"

void Shadow::Init()
{
	GameObject::Init();

	DrawSprite* ds = AddComponent<DrawSprite>();
	ds->Load("asset/texture/shadow.png");
	transform->m_Scale = D3DXVECTOR3(2.0f, 2.0f, 1.0f);


	D3DXQUATERNION quat;
	D3DXVECTOR3 axis = D3DXVECTOR3(1.0f,0.0f,0.0f);
	D3DXQuaternionRotationAxis(&quat, &axis, 3.141592f * 0.5f);
	transform->m_Quaternion *= quat;

	ds->SetMode(DrawSprite::DRAW_MODE::MODE_3D_EDIT);
}

void Shadow::Uninit()
{
	GameObject::Uninit();
}

void Shadow::Update()
{
	GameObject::Update();
}

void Shadow::Draw()
{
	transform->m_Position.y += 0.02f;
	GameObject::Draw();
}
