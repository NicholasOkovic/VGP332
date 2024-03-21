#include "GoalWanderToPosition.h"

#include "GoalSeekToPositionCrow.h"
#include "GoalArriveAtPositionCrow.h"


GoalWanderToPosition::GoalWanderToPosition()
{
}

//void GoalMoveToPosition::SetTileMap(Raven& agent)
//{
//	mTileMap = agent.GetTileMap();
//}

void GoalWanderToPosition::Activate(Crow& agent)
{
	/*TileMap mTileMap; = agent.GetTileMap();*/
	mTileMap.LoadTiles("tiles.txt");
	mTileMap.LoadMap("map.txt");


	mStatus = GoalWanderToPosition::Status::Active;
	RemoveAllSubGoals(agent);


	X::Math::Vector2 startPos = (mTileMap.GetTilePosition(agent.position));


		

	//while end pos is blocked get a new one
	//if (startPos)					///need ot make a check to see if position is in a wall
	//{

	//}

	X::Math::Vector2 endPos;

	do {

		endPos = (X::RandomVector2({ 5.0f, 5.0f }, { X::Math::Vector2(mTileMap.GetColumns() - 1, mTileMap.GetRows() - 1) }));

	} while (mTileMap.IsBlocked(endPos.x, endPos.y));


	Path path = mTileMap.FindPathAStar(endPos.x, endPos.y, startPos.x, startPos.y);		

	float seekDistance = 30;

	/*for (int i = 0; i < path.size() - 1; i++)
	{
		X::DrawScreenLine(path[i].x, path[i].y, path[i + 1].x, path[i + 1].y, X::Colors::Red);
	}*/


	for (int i = 0; i < path.size(); i++)
	{
		//X::DrawScreenLine(path[i].x, path[i].y, path[i + 1].x, path[i + 1].y, X::Colors::Red);

		GoalSeekToPositionCrow* seek = AddSubGoal<GoalSeekToPositionCrow>();
		seek->SetDestination(path[i]);
		seek->SetDestinationRange(seekDistance);
		
	}

}

GoalWanderToPosition::Status GoalWanderToPosition::Process(Crow& agent)
{
	ActivateIfInactive(agent);
	mStatus = ProcessSubGoals(agent);
	ReactivateIfFailed(agent);

	return mStatus;
}

void GoalWanderToPosition::Terminate(Crow& agent)
{
	RemoveAllSubGoals(agent);
	mStatus = GoalWanderToPosition::Status::Inactive;
}

void GoalWanderToPosition::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}


