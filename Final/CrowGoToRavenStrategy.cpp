#include "CrowGoToRavenStrategy.h"

#include "TypeId.h"
#include "GoalCrowMoveToPosition.h"

void CrowGoToRavenStrategy::SetPerception(const AI::PerceptionModule* perception)
{
	mPerception = perception;
}

float CrowGoToRavenStrategy::CalculateDesirability(Crow& agent) const
{
	if (agent.GetState() == CrowState::ChaseRaven)
	{
		const auto& memoryRecords = mPerception->GetMemoryRecords();
		float highestImportance = 0.0f;
		X::Math::Vector2 targetDestination = X::Math::Vector2::Zero();
		for (auto& record : memoryRecords)
		{
			AgentType agentType = static_cast<AgentType>(record.GetProperty<int>("type", 0));
			if (agentType == AgentType::Raven)
			{
				if (record.importance > highestImportance)
				{
					highestImportance = record.importance;
				}
			}
		}
		return highestImportance;
	}
	else
	{
		return 0.0f;
	}
}

std::unique_ptr<AI::Goal<Crow>> CrowGoToRavenStrategy::CreateGoal() const
{

	const auto& memoryRecords = mPerception->GetMemoryRecords();
	float highestImportance = 0.0f;
	X::Math::Vector2 targetDestination = X::Math::Vector2::Zero();

	for (auto& record : memoryRecords)
	{
		AgentType agentType = static_cast<AgentType>(record.GetProperty<int>("type", 0));
		if (agentType == AgentType::Raven)
		{
			if (record.importance > highestImportance)
			{
				highestImportance = record.importance;
				targetDestination = record.GetProperty<X::Math::Vector2>("lastSeenPosition");
			}
		}
	}


	auto newGoal = std::make_unique<GoalCrowMoveToPosition>();
	newGoal->SetDestination(targetDestination);
	return newGoal;
}
