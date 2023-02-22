#include "main.h"
#include "renderer.h"
#include "titlemanager.h"
#include "tool.h"
#include "manager.h"
#include "titlecursor.h"
#include "drawSprite.h"
#include "sprite.h"
#include "input.h"
#include "audio.h"

void TitleManager::Init()
{
	GameObject::Init();
	Scene* scene = Manager::GetInstance()->GetScene();

	m_Cursor = scene->AddGameObject<TitleCursor>(2);

	for (int i = 0; i < m_SpriteNum; i++)
	{
		m_Sprite[i] = scene->AddGameObject<Sprite>(3);
		m_Sprite[i]->SetPosition(Tool::ORIGIN + D3DXVECTOR3(-200.0f, 0.0f + (i * 120.0f), 0.0f));
	}
	m_Sprite[0]->GetComponent<DrawSprite>()->Load("asset/texture/startdot.png");
	m_Sprite[0]->SetScale(D3DXVECTOR3(300.0f, 50.0f, 1.0f));

	m_Sprite[1]->GetComponent <DrawSprite>()->Load("asset/texture/exetdot.png");
	m_Sprite[1]->SetScale(D3DXVECTOR3(250.0f, 50.0f, 1.0f));

	m_SelectNum = 0;
	m_Count = 0.0f;
	m_Start = false;
	m_Click = false;

	m_SpriteDefaultSize = m_Sprite[m_SelectNum]->GetScale();

	m_SE = scene->AddGameObject<Audio>(0);
	m_SE->Load("asset\\sound\\cursol.wav");
	m_SE->SetVolume(0.2f);
}

void TitleManager::Update()
{
	GameObject::Update();

	m_Count += 0.05f;
	if (m_Count >= Tool::PI * 2) m_Count = 0.0f;

	if (!m_Click)
	{
		if (Input::GetKeyTrigger(VK_UP) || Input::GetKeyTrigger('W'))
		{
			if (m_SelectNum > 0)
			{
				m_Sprite[m_SelectNum]->SetScale(m_SpriteDefaultSize);
				m_SelectNum--;
				m_SpriteDefaultSize = m_Sprite[m_SelectNum]->GetScale();
				m_Count = 0.0f;
				m_SE->Play();
			}
		}

		if (Input::GetKeyTrigger(VK_DOWN) || Input::GetKeyTrigger('S'))
		{
			if (m_SelectNum < m_SpriteNum - 1)
			{
				m_Sprite[m_SelectNum]->SetScale(m_SpriteDefaultSize);
				m_SelectNum++;
				m_SpriteDefaultSize = m_Sprite[m_SelectNum]->GetScale();
				m_Count = 0.0f;
				m_SE->Play();
			}
		}

		if (Input::GetKeyTrigger(VK_RETURN) || Input::GetKeyTrigger(VK_LBUTTON))
		{
			m_Click = true;
			switch (m_SelectNum)
			{
			case 0:
				m_Start = true;
				break;
			case 1:
				Manager::GetInstance()->GameExit();
				break;
			default:
				m_Start = true;
				break;
			}
		}
	}


	m_Sprite[m_SelectNum]->SetScale(m_SpriteDefaultSize * (sinf(m_Count) * 0.2f + 1));
	m_Cursor->SetPosition(m_Sprite[m_SelectNum]->GetPosition());
}
