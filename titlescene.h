#pragma once
#include "scene.h"
class TitleScene :
    public Scene
{
public:
	void Init() override;
	void Update() override;

private:
	class TitleManager* m_titleManager = nullptr;
};

