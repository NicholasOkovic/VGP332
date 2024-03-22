#pragma once

#include <Ai.h>
#include "TileMap.h"
#include "Crow.h"

class GoalCrowMoveToPosition : public AI::GoalComposite<Crow>
{
public:
	using Status = AI::Goal<Crow>::Status;

	GoalCrowMoveToPosition();

	void Activate(Crow& agent) override;
	Status Process(Crow& agent) override;
	void Terminate(Crow& agent) override;

	void SetDestination(const X::Math::Vector2& destination);

	//void SetTileMap(TileMap& tileMap);

private:
	//TileMap mTileMap;
	X::Math::Vector2 mDestination;
};
