#include "RavenDepositeStrategy.h"
#include "GoalDepositeMineral.h"

float RavenDepositeStrategy::CalculateDesirability(Raven& agent) const
{
	if (agent.GetState() == RavenState::Deposite)
	{
		return 1000.0f;
	}
	return 0.0f;
}

std::unique_ptr<AI::Goal<Raven>> RavenDepositeStrategy::CreateGoal() const
{
	auto newGoal = std::make_unique<GoalDepositeMineral>();
	return newGoal;
}
