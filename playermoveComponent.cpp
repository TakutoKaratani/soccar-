#include "main.h"
#include "manager.h"
#include "playermoveComponent.h"
#include "input.h"
#include "gameObject.h"
#include "carcontrol.h"
#include "gamecamera.h"

void PlayermoveComponent::Init()
{
	m_CarControl = gameObject->GetComponent<CarControl>();
	if (m_CarControl == nullptr) this->SetDestroy();
}

void PlayermoveComponent::Update()
{
	if (Input::GetKeyPress('A'))
	{
		m_CarControl->LeftTurn();
	}
	if (Input::GetKeyPress('D'))
	{
		m_CarControl->RightTurn();
	}

	if (Input::GetKeyPress('W'))
	{
		m_CarControl->Axel();
	}
	if (Input::GetKeyPress('S'))
	{
		m_CarControl->Back();
	}

	if (Input::GetKeyPress(VK_LBUTTON))
	{
		m_CarControl->Turbo();
	}

	if (Input::GetKeyTrigger(VK_RBUTTON))
	{
		m_CarControl->Jump();
	}

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		GameCamera* gc = Manager::GetInstance()->GetScene()->GetGameObject<GameCamera>();
		if (gc) gc->RotateState();
	}
}
