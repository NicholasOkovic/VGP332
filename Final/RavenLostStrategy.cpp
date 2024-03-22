#include "RavenLostStrategy.h"
#include "GoalRavenWanderToPosition.h"
//#include "GoalWander.h"
//#include "TileMap.h"

float RavenLostStrategy::CalculateDesirability(Raven& agent) const
{
	if (X::Math::Magnitude(agent.position - agent.GetTargetDestination()) <= 100)
	{
		return 250.0f;
	}
	return 5.0f;
}

std::unique_ptr<AI::Goal<Raven>> RavenLostStrategy::CreateGoal() const
{

	auto newGoal = std::make_unique<GoalRavenWanderToPosition>();	
	const float screenWidth = X::GetScreenWidth();
	const float screenHeight = X::GetScreenHeight();


	newGoal->SetDestination(X::RandomVector2({ 10.0f, 10.0f }, { screenWidth - 1, screenHeight - 1 }));


	return newGoal;
}
