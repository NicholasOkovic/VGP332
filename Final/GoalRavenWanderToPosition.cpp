#include "GoalRavenWanderToPosition.h"

#include "GoalSeekToPosition.h"
#include "GoalArriveAtPosition.h"


GoalRavenWanderToPosition::GoalRavenWanderToPosition()
{
}


void GoalRavenWanderToPosition::Activate(Raven& agent)
{
	TileMap* mTileMap = agent.GetTileMap();

	mStatus = GoalRavenWanderToPosition::Status::Active;
	RemoveAllSubGoals(agent);


	X::Math::Vector2 startPos = (mTileMap->GetTilePosition(agent.position));

	X::Math::Vector2 endPos;

	do {

		endPos = (X::RandomVector2({ 5.0f, 5.0f }, { X::Math::Vector2(mTileMap->GetColumns() - 2, mTileMap->GetRows() - 2) }));

	} while (mTileMap->IsBlocked(endPos.x, endPos.y));


	Path path = mTileMap->FindPathAStar(endPos.x, endPos.y, startPos.x, startPos.y);		

	float seekDistance = 30;

	

	for (int i = 0; i < path.size(); i++)
	{

		GoalSeekToPosition* seek = AddSubGoal<GoalSeekToPosition>();
		seek->SetDestination(path[i]);
		seek->SetDestinationRange(seekDistance);
		
	}

}

GoalRavenWanderToPosition::Status GoalRavenWanderToPosition::Process(Raven& agent)
{
	ActivateIfInactive(agent);
	mStatus = ProcessSubGoals(agent);
	ReactivateIfFailed(agent);

	return mStatus;
}

void GoalRavenWanderToPosition::Terminate(Raven& agent)
{
	RemoveAllSubGoals(agent);
	mStatus = GoalRavenWanderToPosition::Status::Inactive;
}

void GoalRavenWanderToPosition::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}


