#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Field.h"
#include "drawSprite.h"

const float Field::size = 500.0f;

void Field::Init()
{
	GameObject::Init();

	m_DepthShadow = true;

	DrawSprite* ds = AddComponent<DrawSprite>();
	ds->Load("asset/texture/Grass004_1K_Color.png");
	ds->SubTextureLoad("asset/texture/Grass004_1K_NormalDX.png");
	ds->SetUV(0.0f, 0.0f, size * 0.125f, size * 0.125f);
	ds->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	ds->SetShader("normalDepthShadowVS.cso", "normalDepthShadowPS.cso");
	transform->m_Scale = D3DXVECTOR3(size, size, 1.0f);


	D3DXQUATERNION quat;
	D3DXVECTOR3 axis = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXQuaternionRotationAxis(&quat, &axis, 3.141592f * 0.5f);
	transform->m_Quaternion *= quat;

	ds->SetMode(DrawSprite::DRAW_MODE::MODE_3D_EDIT);
}

void Field::Uninit()
{
	GameObject::Uninit();
}

void Field::Update()
{
	GameObject::Update();
}

void Field::Draw()
{
	GameObject::Draw();
}