#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "gamecamera.h"
#include "input.h"
#include "player.h"
#include "ball.h"
#include "tool.h"
#include "sprite.h"
#include "drawSprite.h"

void GameCamera::Init()
{
	Camera::Init();
	m_offset = { 0.0f,1.5f,0.0f };
	m_State = new GameCamera::State();
	m_gcs = GameCameraState::None;

	Sprite* sprite = Manager::GetInstance()->GetScene()->AddGameObject<Sprite>(3);
	sprite->SetPosition(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));
	float scale = 300.0f;
	sprite->SetScale(D3DXVECTOR3(scale, scale * 0.33f * 0.56f, 1.0f));
	m_ModeText = sprite->GetDrawSprite();
	m_ModeText->Load("asset/texture/cameraModetext.png");
	m_ModeText->SetMode(DrawSprite::DRAW_MODE::MODE_2D_EDIT_RIGHTBOTTOM);


}

void GameCamera::Uninit()
{
	GameObject::Uninit();
	delete m_State;
}

void GameCamera::Update()
{
	GameObject::Update();

	m_State->Update(this);

	if (m_Statetmp)
	{
		delete m_State;
		m_State = m_Statetmp;
		m_Statetmp = nullptr;
	}
}


void GameCamera::ChangeState(GameCameraState state)
{
	m_gcs = state;
	switch (state)
	{
	case GameCameraState::None:
		m_Statetmp = new GameCamera::State();
		break;

	case GameCameraState::Fixed:
		m_Statetmp = new GameCamera::FixedState();
		m_ModeText->SetUV(0.0f, 0.0f, 1.0f, 0.33f);
		m_ModeText->SetColor(D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f));
		break;

	case GameCameraState::Ball:
		m_Statetmp = new GameCamera::BallState();
		m_ModeText->SetUV(0.0f, 0.33f, 1.0f, 0.66f);
		m_ModeText->SetColor(D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f));
		break;

	case GameCameraState::Free:
		m_Statetmp = new GameCamera::FreeState();
		m_ModeText->SetUV(0.0f, 0.66f, 1.0f, 1.0f);
		m_ModeText->SetColor(D3DXCOLOR(0.6f, 1.0f, 0.6f, 1.0f));
		break;
	}
}

void GameCamera::RotateState()
{
	switch (m_gcs)
	{
	case GameCameraState::Fixed:
		ChangeState(GameCameraState::Free);
		break;

	case GameCameraState::Ball:
		ChangeState(GameCameraState::Fixed);
		break;

	case GameCameraState::Free:
		ChangeState(GameCameraState::Ball);
		break;
	}
}


void GameCamera::State::Update(GameCamera* gc)
{
	m_player = Manager::GetInstance()->GetScene()->GetGameObject<Player>();

	if (m_player) gc->ChangeState(GameCameraState::Free);
}


//プレイヤー正面固定------------------------------
GameCamera::FixedState::FixedState()
{
	m_player = Manager::GetInstance()->GetScene()->GetGameObject<Player>();
}

void GameCamera::FixedState::Update(GameCamera* gc)
{
	D3DXVECTOR3 pos = m_player->GetPosition() + (-m_player->GetForward() * 5) + gc->m_offset;
	gc->SetPosition(pos);
	gc->SetTargetPos(m_player->GetPosition() + gc->m_offset);
}


//ボール追従--------------------------------------
GameCamera::BallState::BallState()
{
	m_player = Manager::GetInstance()->GetScene()->GetGameObject<Player>();
	m_ball = Manager::GetInstance()->GetScene()->GetGameObject<Ball>();
}

void GameCamera::BallState::Update(GameCamera* gc)
{
	D3DXVECTOR3 ballvec, pos;
	ballvec = Tool::Vec3Normalize(m_ball->GetPosition() - (m_player->GetPosition() + gc->m_offset));
	pos = (m_player->GetPosition() + gc->m_offset) - ballvec * 5;
	gc->SetPosition(pos);
	gc->SetTargetPos(m_ball->GetPosition());
}


//フリーカメラ------------------------------------
GameCamera::FreeState::FreeState()
{
	m_player = Manager::GetInstance()->GetScene()->GetGameObject<Player>();
}

void GameCamera::FreeState::Update(GameCamera* gc)
{
	m_rot.x += ((Input::GetCursolPos().x - (SCREEN_WIDTH * 0.5f)) * 0.05f) / 60;
	m_rot.y += ((Input::GetCursolPos().y - (SCREEN_HEIGHT * 0.5f)) * 0.03f) / 60;

	if (m_rot.y > 3)
	{
		m_rot.y = 3;
	}
	else if (m_rot.y < -3)
	{
		m_rot.y = -3;
	}

	if (m_rot.y > 1.55f)
	{
		m_rot.y = 1.55f;
	}
	else if (m_rot.y < -1.55f)
	{
		m_rot.y = -1.55f;
	}

	D3DXVECTOR3 tpos = m_player->GetPosition() + gc->m_offset;
	gc->SetTargetPos(tpos);

	D3DXVECTOR3 campos = D3DXVECTOR3(0.0f, 0.0f, -1.0f) * 5.0f;

	campos.x = campos.z * sinf(m_rot.x) * cosf(m_rot.y);
	campos.z = campos.z * cosf(m_rot.x) * cosf(m_rot.y);

	campos.y = campos.y + (sinf(m_rot.y) * 5.0f);

	campos += m_player->GetPosition();

	gc->SetPosition(campos);
}