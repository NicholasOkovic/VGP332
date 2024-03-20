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

	//X::Math::Vector2 startPos = (agent.position.x, agent.position.y);					///get the easy player pos code from leah
	X::Math::Vector2 startPos = (mTileMap.GetColumns() - 1, mTileMap.GetRows() - 1);

	X::Math::Vector2 endPos = (0, 0);


	Path path = mTileMap.FindPathAStar(startPos.x, startPos.y, endPos.x, endPos.y);		//prolly just need get tile position to input mDestination

	float seekDistance = 30;
	


	for (int i = 0; i < path.size()-1; i++)
	{
		//X::DrawScreenLine(path[i].x, path[i].y, path[i + 1].x, path[i + 1].y, X::Colors::Black);
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


