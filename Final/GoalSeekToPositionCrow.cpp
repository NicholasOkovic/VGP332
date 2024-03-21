#include "GoalSeekToPositionCrow.h"

GoalSeekToPositionCrow::GoalSeekToPositionCrow()
{
}

void GoalSeekToPositionCrow::Activate(Crow& agent)
{
	mStatus = GoalSeekToPositionCrow::Status::Active;
	agent.SetSeek(true);
	agent.destination = mDestination;
}

GoalSeekToPositionCrow::Status GoalSeekToPositionCrow::Process(Crow& agent)
{
	ActivateIfInactive(agent);
	if (X::Math::DistanceSqr(agent.position, mDestination) < mDestinationRange * mDestinationRange)
	{
		mStatus = GoalSeekToPositionCrow::Status::Completed;
	}
	return mStatus;
}

void GoalSeekToPositionCrow::Terminate(Crow& agent)
{
	agent.SetSeek(false);
}

void GoalSeekToPositionCrow::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}

void GoalSeekToPositionCrow::SetDestinationRange(float range)
{
	mDestinationRange = range;
}
