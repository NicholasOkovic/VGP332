#include "RavenGoHomeStrategy.h"
#include "GoalMoveToPosition.h"

float RavenGoHomeStrategy::CalculateDesirability(Raven& agent) const
{
	if (agent.GetState() == RavenState::GoHome)
	{
		return 1000.0f;
	}
	return 0.0f;
}

std::unique_ptr<AI::Goal<Raven>> RavenGoHomeStrategy::CreateGoal() const
{
	auto newGoal = std::make_unique<GoalMoveToPosition>();

	newGoal->SetDestination(X::Math::Vector2(120.0f, 120.0f));

	return newGoal;
}
