#pragma once

#include <AI.h>
#include "Crow.h"

class CrowGoHomeAndSleepUntilRestedState : public AI::State<Crow>
{
public:
	void Enter(Crow& agent) override;
	void Update(Crow& agent, float deltaTime) override;
	void Exit(Crow& agent) override;
	void DebugUI() override;
private:

};

class CrowEnterMineAndDigForNuggetState : public AI::State<Crow>
{
public:
	void Enter(Crow& agent) override;
	void Update(Crow& agent, float deltaTime) override;
	void Exit(Crow& agent) override;
	void DebugUI() override;
private:

};

class CrowQuenchThirstState : public AI::State<Crow>
{
public:
	void Enter(Crow& agent) override;
	void Update(Crow& agent, float deltaTime) override;
	void Exit(Crow& agent) override;
	void DebugUI() override;
private:

};
class CrowVisitBankAndDepositGoldState : public AI::State<Crow>
{
public:
	void Enter(Crow& agent) override;
	void Update(Crow& agent, float deltaTime) override;
	void Exit(Crow& agent) override;
	void DebugUI() override;
private:

};
