#include "main.h"
#include "grassplatform.h"
#include "drawmodel.h"

void GrassPlatform::Init()
{
	GameObject::Init();
	m_DepthShadow = true;

	DrawModel* dm = AddComponent<DrawModel>();
	dm->Load("asset\\model\\grassPlatform.obj");
	dm->LoadSubTexture("asset/texture/Grass004_1K_NormalDX.png");
	dm->SetShader("normalDepthShadowVS.cso", "normalDepthShadowPS.cso");

	transform->m_Scale = D3DXVECTOR3(3.f, 2.f, 3.f);
}