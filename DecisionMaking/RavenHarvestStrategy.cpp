#include "GoToMineralStrategy.h"

#include "TypeId.h"
#include "GoalMoveToPosition.h"
#include "Mineral.h"

float GoalToMineralStrategy::CalculateDesirability(Raven& agent) const
{
	Mineral* mineral = nullptr;
	AI::EntityPtrs minerals = agent.world.GetEntitiesInRange({ agent.destination, 1.0f }, static_cast<uint32_t>(AgentType::Mineral));
	if (!minerals.empty())
	{
		mineral = static_cast<Mineral*>(minerals[0]);
	}

	if (mineral != nullptr && mineral->GetHealth() > 0)
	{
		const Mineral* mineral = (const Mineral*)(agent.target);
		if (X::Math::DistanceSqr(agent.position, agent.destination) < 25.0f)
		{
			return 1000;
		}
	}
	
	return 0.0f;
}


std::unique_ptr<AI::Goal<Raven>> GoalToMineralStrategy::CreateGoal() const
{

	auto newGoal = std::make_unique<GoalMoveToPosition>();
	return newGoal;
}