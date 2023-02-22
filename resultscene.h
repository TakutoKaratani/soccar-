#pragma once
#include "scene.h"
class ResultScene : public Scene
{
public:
	void Init() override;
	void Update() override;

private:
	class ResultManager* m_ResultManager = nullptr;
};