#pragma once
#include "scene.h"
class DioramaScene : public Scene
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
};
