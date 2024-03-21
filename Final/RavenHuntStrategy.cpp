#include "RavenHuntStrategy.h"
#include "GoalMoveToPosition.h"
//#include "GoalWander.h"
//#include "TileMap.h"

float RavenHuntStrategy::CalculateDesirability(Raven& agent) const			//chnaged hunt strat
{
	return 10.0f;
}

std::unique_ptr<AI::Goal<Raven>> RavenHuntStrategy::CreateGoal() const		//chnage wander to follow set path/ go to farming area
{
	/*Path path;
	TileMap tileMap;*/

	//auto newGoal = std::make_unique<GoalWander>();

	//get next positon along path

	auto newGoal = std::make_unique<GoalMoveToPosition>();
	
	newGoal->SetDestination(X::Math::Vector2( 100.0f, 100.0f));

	return newGoal;
}
