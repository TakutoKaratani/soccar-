#include "main.h"
#include "timer.h"

void Timer::Init()
{
	GameObject::Init();
	tUpdate = new Timer::TimerStop();
}

void Timer::Uninit()
{
	GameObject::Uninit();
	delete tUpdate;
}

void Timer::Update()
{
	GameObject::Update();
	tUpdate->Update(this);
}

void Timer::TimerUpdate::Update(Timer* timer)
{
	timer->time -= 1.0f / 60;

	if (timer->time < 0)
	{
		timer->time = 0;
		timer->Stop();
	}
}