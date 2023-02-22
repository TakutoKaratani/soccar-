#include "main.h"
#include "manager.h"
#include "scene.h"
#include "enemy.h"
#include "drawmodel.h"
#include "tool.h"
#include "player.h"
#include "rigidbody.h"
#include "carcontrol.h"
#include "enemyAI.h"
#include "turboparticle.h"

void Enemy::Init()
{
	GameObject::Init();
	DrawModel* dm = AddComponent<DrawModel>();
	dm->Load("asset\\model\\boxelcarblue.obj");
	dm->SetShader("depthShadowMappingVS.cso", "depthShadowMappingPS.cso");

	m_DepthShadow = true;

	m_rb = AddComponent<Rigidbody>();
	m_rb->SetDrag(8.0f);
	m_rb->SetMass(2.0f);
	AddComponent<CarControl>();
	AddComponent<TurboParticle>();

	transform->m_Position = D3DXVECTOR3(0.0f, 0.5f, 5.0f);
	transform->m_Scale = D3DXVECTOR3(1.8f, 1.8f, 1.8f);
}

void Enemy::Uninit()
{
	GameObject::Uninit();
}

void Enemy::Update()
{
	GameObject::Update();


	float groundHeight = 0.0f;

	if (transform->m_Position.y < groundHeight)
	{
		if (m_rb->velocity.y <= 0)
		{
			CarControl* cc = GetComponent<CarControl>();
			if (cc) cc->Landing();
			transform->m_Position.y = groundHeight;
			m_rb->velocity.y = 0.0f;
		}
	}

	PlayerCollision();
}

void Enemy::AIStop()
{
	if (!m_AI) return;
	m_AI->SetDestroy();
	m_AI = nullptr;
}

void Enemy::AIStart()
{
	if (m_AI) return;
	m_AI = AddComponent<EnemyAI>();
}

void Enemy::PlayerCollision()
{

	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	if (!player) return;

	D3DXVECTOR3 back;

	Transform* playerOffset = new Transform(nullptr);
	playerOffset->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.5f));
	Transform* eOffset = new Transform(nullptr);
	eOffset->SetPosition(D3DXVECTOR3(0.0f, transform->m_Scale.y * 0.5f, 0.0f));
	eOffset->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.5f));

	if (Tool::CollisionOBBs(transform, eOffset,
		player->GetTransform(), playerOffset, back))
	{
		if (transform->m_Position.y + back.y < 0 + transform->m_Scale.y * 0.5f)
		{
			back.y = 0;
		}
		transform->m_Position += back;
	}

	delete playerOffset;
	playerOffset = nullptr;
	delete eOffset;
	eOffset = nullptr;
}