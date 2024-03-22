#pragma once

#include <AI.h>
#include "Raven.h"

class RavenGoHome : public AI::State<Raven>
{
public:
	void Enter(Raven& agent) override;
	void Update(Raven& agent, float deltaTime) override;
	void Exit(Raven& agent) override;
	void DebugUI() override;
private:

};

class RavenHarvestMineral : public AI::State<Raven>
{
public:
	void Enter(Raven& agent) override;
	void Update(Raven& agent, float deltaTime) override;
	void Exit(Raven& agent) override;
	void DebugUI() override;
	
private:
	
};

class RavenDeposite : public AI::State<Raven>
{
public:
	void Enter(Raven& agent) override;
	void Update(Raven& agent, float deltaTime) override;
	void Exit(Raven& agent) override;
	void DebugUI() override;
private:

};
class RavenGoToGatherSpot : public AI::State<Raven>
{
public:
	void Enter(Raven& agent) override;
	void Update(Raven& agent, float deltaTime) override;
	void Exit(Raven& agent) override;
	void DebugUI() override;
	void SetPerception(const AI::PerceptionModule* perception);
private:
	const AI::PerceptionModule* mPerception;
};

class RavenGoToMineral : public AI::State<Raven>
{
public:
	void Enter(Raven& agent) override;
	void Update(Raven& agent, float deltaTime) override;
	void Exit(Raven& agent) override;
	void DebugUI() override;
	void SetPerception(const AI::PerceptionModule* perception);
private:
	const AI::PerceptionModule* mPerception;
};

//class RavenNoStrat : public AI::State<Raven>
//{
//public:
//	void Enter(Raven& agent) override;
//	void Update(Raven& agent, float deltaTime) override;
//	void Exit(Raven& agent) override;
//	void DebugUI() override;
//private:
//
//};