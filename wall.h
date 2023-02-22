#pragma once
#include "gameObject.h"

class Wall : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	void Z() {
		delete setPos;
		setPos = new Wall::SetPosZ();
	}

private:
	D3DXCOLOR color;

	class DrawSprite* m_ds = nullptr;
	class GameObject* ball = nullptr;

	class SetPosX
	{
	public:
		virtual void Update(Wall* wall);
	};

	class SetPosZ : public SetPosX
	{
	public:
		void Update(Wall* wall) override;
	};

	SetPosX* setPos = nullptr;
};
