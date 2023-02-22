#include "main.h"
#include "renderer.h"
#include "drawSprite.h"
#include "numbersprite.h"

void NumberSprite::Init()
{
	GameObject::Init();

	SetSplit(10, 1);

	m_ds = AddComponent<DrawSprite>();
	m_ds->Load("asset/texture/numberdot.png");
	m_ds->SetMode(DrawSprite::DRAW_MODE::MODE_2D_EDIT);

	SetNumber(0);
}

void NumberSprite::Uninit()
{
	GameObject::Uninit();

	delete Split_X;
	delete Split_Y;
}

void NumberSprite::SetSplit(int x, int y)
{
	if (x * y < 10)return;
	if (x < 1)x = 1;
	if (y < 1)y = 1;

	if(Split_X) delete Split_X;
	Split_X = new int(x);

	if(Split_Y) delete Split_Y;
	Split_Y = new int(y);
}

void NumberSprite::SetNumber(int num)
{
	if (num > 9) num = 9;
	if (num < 0) num = 0;
	m_number = num;

	float s, t, u, v;

	s = (1.0f / (*Split_X)) * (m_number % (*Split_X));
	u = s + (1.0f / (*Split_X));

	t = (1.0f / (*Split_Y)) * (m_number / (*Split_X));
	v = t + (1.0f / (*Split_Y));

	m_ds->SetUV(s, t, u, v);
}