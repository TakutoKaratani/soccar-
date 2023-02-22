#include "main.h"
#include "manager.h"
#include "scene.h"
#include "soccergoal.h"
#include "drawmodel.h"
#include "tool.h"
#include "ball.h"
#include "goalparticle.h"

void SoccerGoal::Init()
{
	GameObject::Init();
	DrawModel* dm = AddComponent<DrawModel>();
	dm->Load("asset\\model\\soccergoal.obj");

	float scale = 8.0f;

	transform->m_Scale = D3DXVECTOR3(scale, scale, scale);

	m_ParticleSystem = AddComponent<GoalParticle>();
}

void SoccerGoal::Update()
{
	GameObject::Update();

	Ball* ball = Manager::GetInstance()->GetScene()->GetGameObject<Ball>();

	if (ball)
	{
		D3DXVECTOR3 back;
		Transform* offset = new Transform(nullptr);
		offset->SetScale(D3DXVECTOR3(4.0f, 2.f, 2.0f));
		offset->SetPosition(D3DXVECTOR3(0.0f, GetScale().y * 0.5f, 0.0f));
		if (Tool::CollisionOBBAndSphere(transform, offset, ball->GetPosition(), ball->GetScale().x * 0.5f, back))
		{
			m_ParticleSystem->Active();
			m_GoalFrag = true;
		}
		delete offset;
		offset = nullptr;
	}
}

void SoccerGoal::Reset()
{
	m_GoalFrag = false;
	m_ParticleSystem->Reset();
}