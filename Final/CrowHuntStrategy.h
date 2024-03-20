#pragma once

#include <AI.h>

#include "Crow.h"

class CrowHuntStrategy :public AI::Strategy<Crow>
{
public:
	float CalculateDesirability(Crow& agent) const override;
	std::unique_ptr<AI::Goal<Crow>> CreateGoal() const override;

private:

};