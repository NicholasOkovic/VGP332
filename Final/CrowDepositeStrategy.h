#pragma once
#include <Ai.h>

#include "Crow.h"

class CrowDepositeStrategy : public AI::Strategy<Crow>
{
public:
	float CalculateDesirability(Crow& agent) const override;
	std::unique_ptr<AI::Goal<Crow>> CreateGoal() const override;

private:

};
