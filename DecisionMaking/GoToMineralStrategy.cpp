#include "GoToMineralStrategy.h"

#include "TypeId.h"
#include "GoalMoveToPosition.h"

void GoalToMineralStrategy::SetPerception(const AI::PerceptionModule* perception)
{
	mPerception = perception;
}

float GoalToMineralStrategy::CalculateDesirability(Raven& agent) const
{

	const auto& memoryRecords = mPerception->GetMemoryRecords();
	float highestImportance = 0.0f;
	X::Math::Vector2 targetDestination = X::Math::Vector2::Zero();
	for (auto& record : memoryRecords)
	{
		AgentType agentType = static_cast<AgentType>(record.GetProperty<int>("type", 0));
		if (agentType == AgentType::Mineral)
		{
			if (record.importance > highestImportance)
			{
				highestImportance = record.importance;
			}
		}
	}
	return highestImportance;
}

std::unique_ptr<AI::Goal<Raven>> GoalToMineralStrategy::CreateGoal() const
{

	const auto& memoryRecords = mPerception->GetMemoryRecords();
	float highestImportance = 0.0f;
	X::Math::Vector2 targetDestination = X::Math::Vector2::Zero();

	for (auto& record : memoryRecords)
	{
		AgentType agentType = static_cast<AgentType>(record.GetProperty<int>("type", 0));
		if (agentType == AgentType::Mineral)
		{
			if (record.importance > highestImportance)
			{
				highestImportance = record.importance;
				targetDestination = record.GetProperty<X::Math::Vector2>("lastSeenPosition");
			}
		}
	}


	auto newGoal = std::make_unique<GoalMoveToPosition>();
	newGoal->SetDestination(targetDestination);
	return newGoal;
}
