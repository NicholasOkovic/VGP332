#pragma once

#include "AI.h"

enum class Location
{
	Home,
	Mine,
	Saloon,
	Bank
};

enum class MinerState
{
	GoHomeAndSleepTillRested,
	EnterMineAndDigForNugget,
	QuenchThirst,
	VisitBankAndDepositGold
};


class Miner
{
public:
	Miner() = default;
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void ChangeState(MinerState newState);

	void DebugUI();

	//check
	Location GetLocation() const;
	bool IsThirsty() const;
	bool IsPocketFull() const;
	bool IsWealthy() const;
	bool IsRested() const;


	//update state
	void SetLocation(Location location);
	void IncreaseFatigue();
	void AddGoldCarried(int amount);
	void AddGoldToBank();


	void ResetFatigue();
	void ResetThirst();


private:

	AI::StateMachine<Miner> mStateMachine;
	Location mLocation;
	int mGoldCarried;
	int mMoneyInBank;
	int mThirst;
	int mFatigue;


};

