#include "RavenHuntStrategy.h"
#include "GoalMoveToPosition.h"
//#include "GoalWander.h"
//#include "TileMap.h"

float RavenHuntStrategy::CalculateDesirability(Raven& agent) const			//chnaged hunt strat
{
	if (agent.GetState() == RavenState::GoToGatherSpot) //actually kinda cool, they search the premises of the gather spot
	{
		return 200.0f;
	}
	return 10.0f;
}

std::unique_ptr<AI::Goal<Raven>> RavenHuntStrategy::CreateGoal() const		//chnage wander to follow set path/ go to farming area
{
	/*Path path;
	TileMap tileMap;*/

	//auto newGoal = std::make_unique<GoalWander>();

	//get next positon along path

	auto newGoal = std::make_unique<GoalMoveToPosition>();
	
	newGoal->SetDestination(X::Math::Vector2( 550.0f, 450.0f));

	return newGoal;
}
