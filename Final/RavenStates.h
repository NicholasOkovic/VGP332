#pragma once

#include <AI.h>
#include "Raven.h"

class GoHomeAndSleepUntilRestedState : public AI::State<Raven>
{
public:
	void Enter(Raven& agent) override;
	void Update(Raven& agent, float deltaTime) override;
	void Exit(Raven& agent) override;
	void DebugUI() override;
private:

};

class EnterMineAndDigForNuggetState : public AI::State<Raven>
{
public:
	void Enter(Raven& agent) override;
	void Update(Raven& agent, float deltaTime) override;
	void Exit(Raven& agent) override;
	void DebugUI() override;
private:

};

class QuenchThirstState : public AI::State<Raven>
{
public:
	void Enter(Raven& agent) override;
	void Update(Raven& agent, float deltaTime) override;
	void Exit(Raven& agent) override;
	void DebugUI() override;
private:

};
class VisitBankAndDepositGoldState : public AI::State<Raven>
{
public:
	void Enter(Raven& agent) override;
	void Update(Raven& agent, float deltaTime) override;
	void Exit(Raven& agent) override;
	void DebugUI() override;
private:

};
