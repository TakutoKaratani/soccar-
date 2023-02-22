#include "main.h"
#include "manager.h"
#include "scene.h"
#include "box.h"
#include "drawmodel.h"
#include "tool.h"
#include "player.h"
#include "rigidbody.h"

void Box::Init()
{
	GameObject::Init();
	DrawModel* dm = AddComponent<DrawModel>();
	dm ->Load("asset\\model\\centercube\\centercube.obj");
	dm->SetShader("depthShadowMappingVS.cso", "depthShadowMappingPS.cso");
	AddComponent<Rigidbody>();

	m_DepthShadow = true;


	transform->m_Position = D3DXVECTOR3(0.0f, 0.5f, 5.0f);
	transform->m_Scale = D3DXVECTOR3(2.f, 1.f, 3.f);
}

void Box::Uninit()
{
	GameObject::Uninit();
}

void Box::Update()
{
	GameObject::Update();

	if (transform->m_Position.y < 0 + transform->m_Scale.y * 0.5f)
	{
		transform->m_Position.y = transform->m_Scale.y * 0.5f;
	}

	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 back;

	D3DXQUATERNION quat;
	D3DXVECTOR3 axis = Transform::up;
	D3DXQuaternionRotationAxis(&quat, &axis, 0.02f);
	transform->m_Quaternion *= quat;

	if (!Tool::CollisionOBBs(transform,
		player->GetTransform(), back))
	{
		//D3DXQUATERNION quat;
		//D3DXVECTOR3 axis = Transform::up;
		//D3DXQuaternionRotationAxis(&quat, &axis, 0.02f);
		//transform->m_Quaternion *= quat;
	}
	else
	{
		if (transform->m_Position.y + back.y < 0 + transform->m_Scale.y * 0.5f)
		{
			back.y = 0;
		}
		transform->m_Position += back;
	}


}

void Box::Draw()
{
	GameObject::Draw();
}