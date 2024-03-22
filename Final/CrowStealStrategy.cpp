#include "CrowStealStrategy.h"
#include "Raven.h"
#include "TypeId.h"
#include "GoalStealMineralCrow.h"


float CrowStealStrategy::CalculateDesirability(Crow& agent) const
{
	if (agent.GetState() == CrowState::Steal)
	{
		Raven* raven = nullptr;
		AI::EntityPtrs ravens = agent.world.GetEntitiesInRange({ agent.destination, 1.0f }, static_cast<uint32_t>(AgentType::Raven));
		if (!ravens.empty())
		{
			raven = static_cast<Raven*>(ravens[0]);
		}

		if (raven != nullptr && raven->HasMineral())
		{
			const Raven* mineral = (const Raven*)(agent.target);
			if (X::Math::DistanceSqr(agent.position, agent.destination) < 3000.0f)
			{
				return 1000.0f;

			}
		}
	}
	return 0.0f;
}


std::unique_ptr<AI::Goal<Crow>> CrowStealStrategy::CreateGoal() const
{

	auto newGoal = std::make_unique<GoalStealMineralCrow>();
	return newGoal;
}