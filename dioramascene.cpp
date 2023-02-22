#include "main.h"
#include "manager.h"
#include "dioramascene.h"


#include "dioramacamera.h"
#include "player.h"
#include "sky.h"
#include "ball.h"
#include "grassplatform.h"
#include "rigidbody.h"
#include "playermoveComponent.h"
#include "depthtexture.h"
#include "turboparticle.h"
#include "gamelight.h"

TurboParticle* g_tp = nullptr;

void DioramaScene::Init()
{
	m_MainCamera = AddGameObject<DioramaCamera>(0);
	m_Light = AddGameObject<GameLight>(0);
	Sky* s = AddGameObject<Sky>(0);
	s ->SetPosition(D3DXVECTOR3(0.0f, -60.0f, 0.0f));
	s->SetScale(D3DXVECTOR3(100.0f, 100.0f, 100.0f));
	AddGameObject<GrassPlatform>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	Player* p = AddGameObject<Player>(1);
	g_tp = p->GetComponent<TurboParticle>();
	p->DestroyComponent<Rigidbody>();
	p->DestroyComponent<PlayermoveComponent>();
	p->SetPosition(D3DXVECTOR3(0.7f, 1.5f, -0.4f));
	p->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	p->MulQuaternion(Transform::right, -0.5f);
	p->MulQuaternion(Transform::forward, -0.3f);
	p->MulQuaternion(Transform::up, -0.25);



	Ball* b = AddGameObject<Ball>(1);
	b->DestroyComponent<Rigidbody>();
	b->SetScale(D3DXVECTOR3(1.2f, 1.2f, 1.2f));
	b->SetPosition(D3DXVECTOR3(-0.7f, 2.2f, 0.9f));
	b->MulQuaternion(Transform::right, 2.0f);
}

void DioramaScene::Uninit()
{
	Scene::Uninit();
}

void DioramaScene::Update()
{
	Scene::Update();
	g_tp->Active();
}