#include "CrowGoHomeStrategy.h"
#include "GoalCrowMoveToPosition.h"

float CrowGoHomeStrategy::CalculateDesirability(Crow& agent) const
{
	if (agent.GetState() == CrowState::GoHome)
	{
		return 1000.0f;
	}
	return 0.0f;
}

std::unique_ptr<AI::Goal<Crow>> CrowGoHomeStrategy::CreateGoal() const
{
	auto newGoal = std::make_unique<GoalCrowMoveToPosition>();

	newGoal->SetDestination(X::Math::Vector2(120.0f, 120.0f));

	return newGoal;
}
