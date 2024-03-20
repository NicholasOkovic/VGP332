#include "GoalWander.h"

GoalWander::GoalWander()
{
}

void GoalWander::Activate(Crow& agent)
{
	mStatus = GoalWander::Status::Active;
	agent.SetWander(true);
}

GoalWander::Status GoalWander::Process(Crow& agent)
{
	ActivateIfInactive(agent);
	return mStatus;
}

void GoalWander::Terminate(Crow& agent)
{
	agent.SetWander(false);
}
