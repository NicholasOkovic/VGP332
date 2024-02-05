#pragma once


#include <AI.h>
#include "Person.h"

class GoHomeAndSleepState : public AI::State<Person>
{
public:
	void Enter(Person& agent) override;
	void Update(Person& agent, float deltaTime) override;
	void Exit(Person& agent) override;
	void DebugUI() override;
private:

};

class StartWorkingState : public AI::State<Person>
{
public:
	void Enter(Person& agent) override;
	void Update(Person& agent, float deltaTime) override;
	void Exit(Person& agent) override;
	void DebugUI() override;
private:

};

class DrinkState : public AI::State<Person>
{
public:
	void Enter(Person& agent) override;
	void Update(Person& agent, float deltaTime) override;
	void Exit(Person& agent) override;
	void DebugUI() override;
private:

};
class EatState : public AI::State<Person>
{
public:
	void Enter(Person& agent) override;
	void Update(Person& agent, float deltaTime) override;
	void Exit(Person& agent) override;
	void DebugUI() override;
private:

};
