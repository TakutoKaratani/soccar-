#pragma once
#include "component.h"

class PlayermoveComponent : public Component
{
public:
	PlayermoveComponent(class GameObject* go)
		:Component(go){}

	void Init();
	void Update();

private:
	class CarControl* m_CarControl = nullptr;
};
