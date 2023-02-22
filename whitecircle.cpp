#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "whitecircle.h"
#include "drawSprite.h"

void WhiteCircle::Init()
{
	GameObject::Init();

	DrawSprite* ds = AddComponent<DrawSprite>();
	ds->Load("asset/texture/whitecircle.png");
	transform->m_Scale = D3DXVECTOR3(2.0f, 2.0f, 1.0f);

	ds->SetShader("depthShadowMappingVS.cso", "depthShadowMappingPS.cso");


	D3DXQUATERNION quat;
	D3DXVECTOR3 axis = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXQuaternionRotationAxis(&quat, &axis, 3.141592f * 0.5f);
	transform->m_Quaternion *= quat;

	ds->SetMode(DrawSprite::DRAW_MODE::MODE_3D_EDIT);
}

void WhiteCircle::Uninit()
{
	GameObject::Uninit();
}

void WhiteCircle::Update()
{
	GameObject::Update();
}

void WhiteCircle::Draw()
{
	GameObject::Draw();
}