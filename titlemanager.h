#pragma once
#include "gameObject.h"
class TitleManager : public GameObject
{
public:
	void Init() override;
	void Update() override;

	bool GetStart() { return m_Start; }
private:
	static const int m_SpriteNum = 2;
	class Sprite* m_Sprite[m_SpriteNum]{};
	class GameObject* m_Cursor = nullptr;

	D3DXVECTOR3 m_SpriteDefaultSize{};
	float m_Count = 0;

	int m_SelectNum = 0;
	bool m_Click = false;
	bool m_Start = false;

	class Audio* m_SE = nullptr;
};
