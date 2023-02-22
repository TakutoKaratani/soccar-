#pragma once
#include "camera.h"

class GameCamera : public Camera
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	enum class GameCameraState
	{
		None,
		Fixed,
		Ball,
		Free,
	};

	void ChangeState(GameCameraState state);
	void RotateState();

private:
	GameCameraState m_gcs = GameCameraState::None;
	class DrawSprite* m_ModeText = nullptr;

	class State
	{
	public:
		State(){}
		virtual ~State(){}
		virtual void Update(GameCamera* gc);

	protected:
		GameObject* m_player = nullptr;
	};

	class FixedState : public State
	{
	public:
		FixedState();
		void Update(GameCamera* gc);
	};

	class BallState : public State
	{
	public:
		BallState();
		void Update(GameCamera* gc);

	private:
		GameObject* m_ball = nullptr;
	};

	class FreeState : public State
	{
	public:
		FreeState();
		void Update(GameCamera* gc);

	private:
		D3DXVECTOR2 m_rot = { 0.0f,0.0f };
	};

	GameCamera::State* m_State = nullptr;
	GameCamera::State* m_Statetmp = nullptr;
};
