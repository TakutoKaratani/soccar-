#pragma once
#include "gameObject.h"

class Timer : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	void SetTime(float t) { time = t; }
	void Start()
	{
		if (tUpdate) delete tUpdate;
		tUpdate = new Timer::TimerUpdate();
	}
	void Stop()
	{
		if (tUpdate) delete tUpdate;
		tUpdate = new Timer::TimerStop();
	}

	float GetTime() { return time; }

private:
	float time = 0;
	

	class TimerUpdate
	{
	public:
		virtual void Update(Timer* timer);
	};

	class TimerStop : public TimerUpdate
	{
		void Update(Timer* timer) {}
	};

	TimerUpdate* tUpdate = nullptr;
};
