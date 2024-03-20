#pragma once
#include <Ai.h>

#include "Raven.h"

class RavenHarvestStrategy : public AI::Strategy<Raven>
{
public:
	void SetPerception(const AI::PerceptionModule* perception);

	float CalculateDesirability(Raven& agent) const override;
	std::unique_ptr<AI::Goal<Raven>> CreateGoal() const override;

private:
	const AI::PerceptionModule* mPerception;

};