#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "tutorialscene.h"
#include "gamescene.h"
#include "fade.h"

#include "input.h"

#include "titlecamera.h"
#include "light.h"
#include "sprite.h"
#include "drawSprite.h"

void TutorialScene::Init()
{
	m_MainCamera = AddGameObject<TitleCamera>(0);
	m_Light = AddGameObject<Light>(0);

	Sprite* sprite = AddGameObject<Sprite>(2);
	sprite->SetScale(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 1.0f));
	sprite->GetDrawSprite()->Load("asset/texture/tutorial.png");
}

void TutorialScene::Update()
{
	Scene::Update();
	if (Input::GetKeyTrigger(VK_LBUTTON) && !Fade::GetInstance()->IsFade())
	{
		Fade::GetInstance()->SetMode(Fade::FADE_MODE::MODE_ALPHA);
		Fade::GetInstance()->SetSpeed(0.6f);
		Fade::GetInstance()->FadeIn<GameScene>();
	}
}