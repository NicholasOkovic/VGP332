#include "GoalArriveAtPositionCrow.h"

GoalArriveAtPositionCrow::GoalArriveAtPositionCrow()
{
}

void GoalArriveAtPositionCrow::Activate(Crow& agent)
{
	mStatus = GoalArriveAtPositionCrow::Status::Active;
	agent.SetArrive(true);
	agent.destination = mDestination;
}

GoalArriveAtPositionCrow::Status GoalArriveAtPositionCrow::Process(Crow& agent)
{
	ActivateIfInactive(agent);
	if (X::Math::DistanceSqr(agent.position, mDestination) < 25.0f)
	{
		mStatus = GoalArriveAtPositionCrow::Status::Completed;
	}
	return mStatus;
}

void GoalArriveAtPositionCrow::Terminate(Crow& agent)
{
	agent.SetArrive(false);
}

void GoalArriveAtPositionCrow::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}
