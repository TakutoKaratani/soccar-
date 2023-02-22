
#include "main.h"
#include "input.h"


BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];
POINT Input::point;
bool Input::showCursol;

void Input::Init()
{

	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );
	GetCursorPos(&point);
	ShowCursolFlag(false);
	showCursol = false;
}

void Input::Uninit()
{


}

void Input::Update()
{
	if (GetActiveWindow())
	{
		memcpy(m_OldKeyState, m_KeyState, 256);

		GetKeyboardState(m_KeyState);
		GetCursorPos(&point);

		if(!showCursol)
		SetCursorPos((int)(SCREEN_WIDTH * 0.5f), (int)(SCREEN_HEIGHT * 0.5f));
	}

	if (Input::GetKeyTrigger('K'))
	{
		if (showCursol) showCursol = false;
		else showCursol = true;

		ShowCursolFlag(showCursol);
	}
}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

void Input::ShowCursolFlag(bool flag)
{
	ShowCursor(flag);
}

D3DXVECTOR2 Input::GetCursolPos()
{
	return D3DXVECTOR2((float)point.x,(float)point.y);
}
