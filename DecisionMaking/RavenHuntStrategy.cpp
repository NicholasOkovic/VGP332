#include "RavenHuntStrategy.h"

#include "GoalWander.h"


float RavenHuntSTrategy::CalculateDesirability(Raven& agent) const
{
	return 10.0f;
}

std::unique_ptr<AI::Goal<Raven>> RavenHuntSTrategy::CreateGoal() const
{
	auto newGoal = std::make_unique<GoalWander>();
	
	return newGoal;
}
