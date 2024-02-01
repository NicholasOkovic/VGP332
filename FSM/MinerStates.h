#pragma once

#include <AI.h>
#include "Miner.h"

class GoHomeAndSleepUntilRestedState : public AI::State<Miner>
{
public:
	void Enter(Miner& agent) override;
	void Update(Miner& agent, float deltaTime) override;
	void Exit(Miner& agent) override;
	void DebugUI() override;
private:

};

class EnterMineAndDigForNuggetState : public AI::State<Miner>
{
public:
	void Enter(Miner& agent) override;
	void Update(Miner& agent, float deltaTime) override;
	void Exit(Miner& agent) override;
	void DebugUI() override;
private:

};

class QuenchThirstState : public AI::State<Miner>
{
public:
	void Enter(Miner& agent) override;
	void Update(Miner& agent, float deltaTime) override;
	void Exit(Miner& agent) override;
	void DebugUI() override;
private:

};
class VisitBankAndDepositGoldState : public AI::State<Miner>
{
public:
	void Enter(Miner& agent) override;
	void Update(Miner& agent, float deltaTime) override;
	void Exit(Miner& agent) override;
	void DebugUI() override;
private:

};
