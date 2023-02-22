#pragma once
#include "manager.h"
#include "fadebase.h"

class Fade
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool IsFade()
	{
		if (!m_FadeBase) return false;
		if (m_FadeBase->GetFadeState() == m_FadeBase->FADE_STATE::FADE_NONE) return false;
		else return true;
	}

	void SetSpeed(float speed)
	{
		if (!m_FadeBase) return;
		m_FadeBase->SetSpeed(speed);
	}

	template <typename T>
	void FadeIn()
	{
		if (!m_FadeBase) return;
		m_NextScene = new T();
		m_FadeBase->FadeIn();
	}

	template <typename T>
	void FadeOut()
	{
		if (!m_FadeBase) return;
		Manager::GetInstance()->SetScene<T>();
		m_FadeBase->FadeOut();
	}

	void FadeOut()
	{
		Manager::GetInstance()->SetScene(m_NextScene);
		m_NextScene = nullptr;
	}

	static Fade* GetInstance() {
		return s_pInstance;
	}

	static void Create()
	{
		if (!s_pInstance)
		{
			s_pInstance = new Fade();
		}
	}
	static void Destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	enum FADE_MODE
	{
		MODE_ALPHA,
		MODE_SCROLL_SIDE,
		MODE_CURTAIN,
	};

	void SetMode(FADE_MODE mode);

private:
	static Fade* s_pInstance;
	FadeBase* m_FadeBase = nullptr;

	class Scene* m_NextScene = nullptr;
};

