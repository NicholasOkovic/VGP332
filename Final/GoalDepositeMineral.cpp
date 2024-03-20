#include "GoalDepositeMineral.h"
#include "TypeId.h"

GoalDepositeMineral::GoalDepositeMineral()
{
}

void GoalDepositeMineral::Activate(Raven& agent)
{
	mStartTime = X::GetTime();
	/*AI::EntityPtrs mineral = agent.world.GetEntitiesInRange({ agent.destination, 1.0f }, static_cast<uint32_t>(AgentType::Mineral));
	if (!mineral.empty())
	{
		agent.target = static_cast<AI::Agent*>(mineral[0]);
	}*/

}

GoalDepositeMineral::Status GoalDepositeMineral::Process(Raven& agent)	//prolly doesnt work
{

	if (mStartTime + 5.0f < X::GetTime())
	{
		agent.target = nullptr;
		mStatus = GoalDepositeMineral::Status::Completed;		

	}
	return mStatus;
}

void GoalDepositeMineral::Terminate(Raven& agent)
{
}
