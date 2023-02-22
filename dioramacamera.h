#pragma once
#include "camera.h"

class DioramaCamera : public Camera
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

};