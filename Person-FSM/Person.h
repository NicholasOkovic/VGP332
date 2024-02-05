#pragma once

#include "AI.h"

enum class Location
{
	Home,
	Work,
	Starbucks,
	Restaurant
};

enum class PersonState
{
	GoHomeAndSleep,
	StartWorking,
	Drink,
	Eat
};


class Person
{
public:
	Person() = default;
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void ChangeState(PersonState newState);

	void DebugUI();

	//check
	Location GetLocation() const;
	bool IsThirsty() const;
	bool IsHungry() const;


	bool IsWealthy() const;
	bool IsDayOver() const;
	bool IsRentDue() const;

	//update state
	void SetLocation(Location location);
	void TimePassed();
	void AddMoney(int amount);
	void SpendMoney(int amount);

	void ResetDay();
	void ResetThirst();
	void ResetHunger();


private:

	AI::StateMachine<Person> mStateMachine;
	Location mLocation;

	int mMoney;
	int mThirst;
	int mHunger;
	int mTime;
	int mDay;

};

