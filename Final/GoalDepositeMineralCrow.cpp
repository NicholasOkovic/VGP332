#include "GoalDepositeMineralCrow.h"
#include "TypeId.h"

extern int crowDeposites;

GoalDepositeMineralCrow::GoalDepositeMineralCrow()
{
}

void GoalDepositeMineralCrow::Activate(Crow& agent)
{
	mStartTime = X::GetTime();
	/*AI::EntityPtrs mineral = agent.world.GetEntitiesInRange({ agent.destination, 1.0f }, static_cast<uint32_t>(AgentType::Mineral));
	if (!mineral.empty())
	{
		agent.target = static_cast<AI::Agent*>(mineral[0]);
	}*/

}

GoalDepositeMineralCrow::Status GoalDepositeMineralCrow::Process(Crow& agent)	//prolly doesnt work
{

	if (mStartTime + 5.0f < X::GetTime())
	{
		agent.target = nullptr;
		mStatus = GoalDepositeMineralCrow::Status::Completed;
		agent.SetMineral(false);
		crowDeposites++;
	}
	return mStatus;
}

void GoalDepositeMineralCrow::Terminate(Crow& agent)
{
}
