#include "Person.h"
#include "PersonStates.h"
#include <ImGui/Inc/imgui.h>

void Person::Initialize()
{
	mLocation = Location::Home;
	mMoney = 0;
	mThirst = 0;
	mTime = 0;
	mHunger = 0;

	mStateMachine.Initialize(this);
	mStateMachine.AddState<GoHomeAndSleepState>();
	mStateMachine.AddState<StartWorkingState>();
	mStateMachine.AddState<DrinkState>();
	mStateMachine.AddState<EatState>();
	ChangeState(PersonState::GoHomeAndSleep);
}

void Person::Terminate()
{
	mStateMachine.Terminate();
}

void Person::Update(float deltaTime)
{
	mStateMachine.Update(deltaTime);
}

void Person::ChangeState(PersonState newState)
{
	mStateMachine.ChangeState((int)newState);
}

void Person::DebugUI()
{
	mStateMachine.DebugUI();
	ImGui::Text("Status: Money[%d] Hunger[%d] Thirst[%d] Time[%d], Day[%d]", mMoney, mHunger, mThirst, mTime, mDay);
}

Location Person::GetLocation() const
{
	return Location();
}

bool Person::IsThirsty() const
{
	return mThirst >= 5;
}

bool Person::IsHungry() const
{
	return mHunger >= 8;
}

bool Person::IsWealthy() const
{
	return mMoney >= 1000000;
}

bool Person::IsDayOver() const
{
	return mTime >= 12;
}

bool Person::IsRentDue() const 
{
	return (mDay % 15 == 0);
}

void Person::SetLocation(Location location)
{
	mLocation = location;
}

void Person::TimePassed()
{
	++mTime;
	++mThirst;
	++mHunger;
}
void Person::AddMoney(int amount)
{
	mMoney += amount;
}

void Person::SpendMoney(int amount)
{
	mMoney -= amount;
}

void Person::ResetDay()
{
	mTime = 0;
	mDay += 1;
}

void Person::ResetThirst()
{
	mThirst = 0;
}

void Person::ResetHunger()
{
	mHunger = 0;
}
