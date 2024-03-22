#pragma once
#include <Ai.h>

#include "Raven.h"

class RavenDepositeStrategy : public AI::Strategy<Raven>
{
public:
	float CalculateDesirability(Raven& agent) const override;
	std::unique_ptr<AI::Goal<Raven>> CreateGoal() const override;

private:

};
