#pragma once


#include <Ai.h>

#include "Crow.h"

class CrowGoToRavenStrategy : public AI::Strategy<Crow>
{
public:
	void SetPerception(const AI::PerceptionModule* perception);

	float CalculateDesirability(Crow& agent) const override;
	std::unique_ptr<AI::Goal<Crow>> CreateGoal() const override;

private:
	const AI::PerceptionModule* mPerception;

};