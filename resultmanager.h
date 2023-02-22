#pragma once
#include "gameObject.h"

class ResultManager : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	bool ChangeScene() { return changeScene; }

private:
	bool changeScene = false;
	int m_Point[2]{};

	void LoadScore();
};
