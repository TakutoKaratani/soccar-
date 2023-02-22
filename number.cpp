#include "main.h"
#include "manager.h"
#include "number.h"

void Number::Init()
{
	GameObject::Init();
	m_num = 0;
	m_MaxNum = 1000;
	m_ZeroCover = false;
	m_mode = Number::MODE::LEFT;
	m_ss = new Number::SpriteSeter();

	SetNumber(m_num);
}

void Number::Uninit()
{
	GameObject::Uninit();
	DestroySprite();
	delete m_ss;
}

void Number::Update()
{
	GameObject::Update();
}

void Number::SetNumber(int num)
{
	if (num < 0) num = 0;
	if (num > m_MaxNum) num = m_MaxNum;
	m_num = num;

	m_ss->SpriteSet(this);
}

int Number::CheckDigit(int num)
{
	int digit = 1;
	for (int i = 10; i < num + 1; i *= 10)
	{
		digit++;
	}
	return digit;
}

void Number::Resize(int digit)
{
	DestroySprite();
	Scene* scene = Manager::GetInstance()->GetScene();
	for (int i = 0; i < digit; i++)
	{
		NumberSprite* ns = scene->AddGameObject<NumberSprite>(3);
		ns->SetScale(GetScale());
		m_Sprite.push_back(ns);
	}
}


void Number::SetNumberSprite()
{
	int num = m_num;
	for (unsigned int i = 0; i < m_Sprite.size(); i++)
	{
		m_Sprite[i]->SetNumber(num % 10);
		num /= 10;
	}

	int i = 0;

	switch (m_mode)
	{
	case Number::MODE::LEFT:
		i = m_Sprite.size() - 1;
		for (NumberSprite* ns : m_Sprite)
		{
			D3DXVECTOR3 pos = GetPosition();
			pos.x += m_Interval * i;
			ns->SetPosition(pos);
			i--;
		}
		break;
	case Number::MODE::RIGHT:
		i = 0;
		for (NumberSprite* ns : m_Sprite)
		{
			D3DXVECTOR3 pos = GetPosition();
			pos.x -= m_Interval * i;
			ns->SetPosition(pos);
			i++;
		}
		break;
	}
}

void Number::SpriteSeter::SpriteSet(Number* Number)
{
	Number->Resize(Number->CheckDigit(Number->m_num));
	Number->SetNumberSprite();
}

void Number::SpriteSeterZeroCover::SpriteSet(Number* Number)
{
	Number->Resize(Number->CheckDigit(Number->m_MaxNum));
	Number->SetNumberSprite();
}