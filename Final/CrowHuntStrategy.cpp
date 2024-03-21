#include "CrowHuntStrategy.h"
#include "GoalWanderToPosition.h"
//#include "GoalWander.h"
//#include "TileMap.h"

float CrowHuntStrategy::CalculateDesirability(Crow& agent) const			
{
	return 5.0f;
}

std::unique_ptr<AI::Goal<Crow>> CrowHuntStrategy::CreateGoal() const		
{
	/*Path path;
	TileMap tileMap;*/

	//auto newGoal = std::make_unique<GoalWander>();

	auto newGoal = std::make_unique<GoalWanderToPosition>();
	const float screenWidth = X::GetScreenWidth();
	const float screenHeight = X::GetScreenHeight();

	
	newGoal->SetDestination(X::RandomVector2({ 10.0f, 10.0f }, { screenWidth-1, screenHeight-1 }));


	return newGoal;
}
