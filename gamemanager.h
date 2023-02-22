#pragma once
#include "gameObject.h"

class GameManager : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	bool ChangeResult() { return m_ChangeScene; }

private:
	void Reset();

	bool m_StopGame = false;
	bool m_ChangeScene = false;

	int m_Point[2] = { 0,0 };

	class Timer* timer = nullptr;

	GameObject* m_Player = nullptr;
	class Enemy* m_Enemy = nullptr;
	GameObject* m_Ball = nullptr;
	class SoccerGoal* m_Goal[2] = { nullptr,nullptr };
	class ScoreBord* m_ScoreBord = nullptr;

	class Audio* m_SE[2]{};

	class GameUpdate
	{
	public:
		virtual void Update(GameManager* gm);
	};

	class GameUpdateStart : public GameUpdate
	{
	public:
		GameUpdateStart();
		void Update(GameManager* gm);

	private:
		class Number* countSprite = nullptr;
		class Timer* startTimer = nullptr;
		float startTime = 3.0f;
	};

	class GameUpdateFinish : public GameUpdate
	{
	public:
		GameUpdateFinish();
		void Update(GameManager* gm);

	private:
		class Timer* finishTimer = nullptr;
		float finishTime = 3.0f;
	};

	class GameUpdateGoal : public GameUpdate
	{
	public:
		GameUpdateGoal();

		void Update(GameManager* gm);

	private:
		class Timer* resetTimer = nullptr;
		float resetTime = 3.5f;
	};

	GameUpdate* gUpdate = nullptr;
};