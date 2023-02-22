#pragma once
#include "scene.h"
class GameScene : public Scene
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	class GameManager* m_GM = nullptr;
};

