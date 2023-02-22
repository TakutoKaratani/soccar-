#pragma once


class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
	static POINT point;
	static bool showCursol;
public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );
	static void ShowCursolFlag(bool flag);
	static D3DXVECTOR2 GetCursolPos();

};
