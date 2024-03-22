#include "GoalCrowMoveToPosition.h"

#include "GoalSeekToPositionCrow.h"
#include "GoalArriveAtPositionCrow.h"


GoalCrowMoveToPosition::GoalCrowMoveToPosition()
{
}

//void GoalMoveToPosition::SetTileMap(Raven& agent)
//{
//	mTileMap = agent.GetTileMap();
//}

void GoalCrowMoveToPosition::Activate(Crow& agent)
{
	TileMap* mTileMap = agent.GetTileMap();
	
	mStatus = GoalCrowMoveToPosition::Status::Active;
	RemoveAllSubGoals(agent);				
	X::Math::Vector2 startPos = mTileMap->GetTilePosition(agent.position);
	X::Math::Vector2 endPos = mTileMap->GetTilePosition(mDestination);
	agent.SetTargetDestination(mDestination);

	Path path = mTileMap->FindPathAStar(endPos.x, endPos.y, startPos.x, startPos.y);		//prolly just need get tile position to input mDestination

	float seekDistance = 30;
	


	for (int i = 0; i < path.size(); i++)
	{
		
		if (i == path.size())
		{
			GoalArriveAtPositionCrow* arrive = AddSubGoal<GoalArriveAtPositionCrow>();
			arrive->SetDestination(path[i]);
		}
		else
		{
			GoalSeekToPositionCrow* seek = AddSubGoal<GoalSeekToPositionCrow>();
			seek->SetDestination(path[i]);
			seek->SetDestinationRange(seekDistance);
		}
		
		
	}
}

GoalCrowMoveToPosition::Status GoalCrowMoveToPosition::Process(Crow& agent)
{
	ActivateIfInactive(agent);
	mStatus = ProcessSubGoals(agent);
	ReactivateIfFailed(agent);

	return mStatus;
}

void GoalCrowMoveToPosition::Terminate(Crow& agent)
{
	RemoveAllSubGoals(agent);
	mStatus = GoalCrowMoveToPosition::Status::Inactive;
}

void GoalCrowMoveToPosition::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}


