#include "GoalStealMineralCrow.h"
#include "TypeId.h"

GoalStealMineralCrow::GoalStealMineralCrow()
{
}

void GoalStealMineralCrow::Activate(Crow& agent)
{
	mStartTime = X::GetTime();
	/*AI::EntityPtrs mineral = agent.world.GetEntitiesInRange({ agent.destination, 1.0f }, static_cast<uint32_t>(AgentType::Mineral));
	if (!mineral.empty())
	{
		agent.target = static_cast<AI::Agent*>(mineral[0]);
	}*/

}

GoalStealMineralCrow::Status GoalStealMineralCrow::Process(Crow& agent)
{
	Raven* raven = nullptr;
	AI::EntityPtrs ravens = agent.world.GetEntitiesInRange({ agent.destination, 1.0f }, static_cast<uint32_t>(AgentType::Raven));
	if (!ravens.empty())
	{
		raven = static_cast<Raven*>(ravens[0]);
	}

	if (raven == nullptr)
	{
		mStatus = GoalStealMineralCrow::Status::Failed;
	}
	else if (mStartTime + 5.0f < X::GetTime())
	{
		
		raven->SetMineral(false);
		agent.target = nullptr;
		agent.SetMineral(true);
		mStatus = GoalStealMineralCrow::Status::Completed;

	}
	return mStatus;
}

void GoalStealMineralCrow::Terminate(Crow& agent)
{
}
