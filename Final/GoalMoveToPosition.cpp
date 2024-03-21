#include "GoalMoveToPosition.h"

#include "GoalSeekToPosition.h"
#include "GoalArriveAtPosition.h"


GoalMoveToPosition::GoalMoveToPosition()
{
}

//void GoalMoveToPosition::SetTileMap(Raven& agent)
//{
//	mTileMap = agent.GetTileMap();
//}

void GoalMoveToPosition::Activate(Raven& agent)
{
	TileMap mTileMap; /*= agent.GetTileMap();*/
	mTileMap.LoadTiles("tiles.txt");
	mTileMap.LoadMap("map.txt");

	
	mStatus = GoalMoveToPosition::Status::Active;
	RemoveAllSubGoals(agent);				
	X::Math::Vector2 startPos = mTileMap.GetTilePosition(agent.position);
	X::Math::Vector2 endPos = mTileMap.GetTilePosition(mDestination);


	Path path = mTileMap.FindPathAStar(endPos.x, endPos.y, startPos.x, startPos.y);		//prolly just need get tile position to input mDestination

	float seekDistance = 30;
	


	for (int i = 0; i < path.size(); i++)
	{
		
		if (i == path.size())
		{
			GoalArriveAtPosition* arrive = AddSubGoal<GoalArriveAtPosition>();
			arrive->SetDestination(path[i]);
		}
		else
		{
			GoalSeekToPosition* seek = AddSubGoal<GoalSeekToPosition>();
			seek->SetDestination(path[i]);
			seek->SetDestinationRange(seekDistance);
		}
		
		
	}
}

GoalMoveToPosition::Status GoalMoveToPosition::Process(Raven& agent)
{
	ActivateIfInactive(agent);
	mStatus = ProcessSubGoals(agent);
	ReactivateIfFailed(agent);

	return mStatus;
}

void GoalMoveToPosition::Terminate(Raven& agent)
{
	RemoveAllSubGoals(agent);
	mStatus = GoalMoveToPosition::Status::Inactive;
}

void GoalMoveToPosition::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}


