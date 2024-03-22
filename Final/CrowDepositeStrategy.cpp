#include "CrowDepositeStrategy.h"
#include "GoalDepositeMineralCrow.h"

float CrowDepositeStrategy::CalculateDesirability(Crow& agent) const
{
	if (agent.GetState() == CrowState::Deposite)
	{
		return 1000.0f;
	}
	return 0.0f;
}

std::unique_ptr<AI::Goal<Crow>> CrowDepositeStrategy::CreateGoal() const
{
	auto newGoal = std::make_unique<GoalDepositeMineralCrow>();
	return newGoal;
}
