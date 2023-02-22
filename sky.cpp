#include "main.h"
#include "manager.h"
#include "scene.h"
#include "sky.h"
#include "drawmodel.h"
#include "simplerotation.h"

void Sky::Init()
{
	GameObject::Init();
	DrawModel* d3 = AddComponent<DrawModel>();
	d3->Load("asset\\model\\sky.obj");
	d3->Lighting(false);

	AddComponent<SimpleRotation>()->SetSpeed(0.0001f);

	transform->m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	transform->m_Scale = D3DXVECTOR3(700.0f, 700.0f, 700.0f);
}

void Sky::Uninit()
{
	GameObject::Uninit();
}

void Sky::Update()
{
	GameObject::Update();
	if (!m_pOrigin)
	{
		m_pOrigin = Manager::GetInstance()->GetScene()->GetGameObject<Camera>();
	}

	if (m_pOrigin)
	{
		transform->m_Position.x = m_pOrigin->GetPosition().x;
		transform->m_Position.z = m_pOrigin->GetPosition().z;
	}
}

void Sky::Draw()
{
	GameObject::Draw();
}