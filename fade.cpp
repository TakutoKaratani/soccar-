#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "texturemanager.h"
#include "fadealpha.h"
#include "fadeScrollSide.h"
#include "fadeCurtain.h"

Fade* Fade::s_pInstance = nullptr;

void Fade::Init()
{
	m_FadeBase = new FadeAlpha();
	m_FadeBase->Init();
}

void Fade::Uninit()
{
	if (m_FadeBase)
	{
		m_FadeBase->Uninit();
		delete m_FadeBase;
		m_FadeBase = nullptr;
	}
}

void Fade::Update()
{
	if (!m_FadeBase) return;

	bool changescene = false;
	if (m_FadeBase->GetFadeState() == m_FadeBase->FADE_STATE::FADE_IN) {
		changescene = true;
	}

	m_FadeBase->Update();

	if (changescene &&
		m_FadeBase->GetFadeState() == m_FadeBase->FADE_STATE::FADE_OUT) {
		this->FadeOut();
	}
}

void Fade::Draw()
{
	if (!IsFade()) return;
	m_FadeBase->Draw();
}

void Fade::SetMode(FADE_MODE mode)
{
	if (m_FadeBase)
	{
		if (m_FadeBase->GetFadeState() != m_FadeBase->FADE_STATE::FADE_NONE) return;
		m_FadeBase->Uninit();
		delete m_FadeBase;
	}

	switch (mode)
	{
	case FADE_MODE::MODE_ALPHA:
		m_FadeBase = new FadeAlpha();
		break;
	case FADE_MODE::MODE_SCROLL_SIDE:
		m_FadeBase = new FadeScrollSide();
		break;
	case FADE_MODE::MODE_CURTAIN:
		m_FadeBase = new FadeCurtain();
		break;
	default:
		m_FadeBase = new FadeAlpha();
		break;
	}

	m_FadeBase->Init();
}
