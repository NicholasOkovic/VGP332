#pragma once

#include "Goal.h"

namespace AI {


	template<class AgentType>
	class GoalComposite : public Goal<AgentType>
	{
	public:

		using STatus = Goal<AgentType>::Status;

		GoalComposite() = default;
		virtual ~GoalComposite() = default;

	protected:

		template<class GoalType>
		GoalType* AddSubGoal()
		{
			static_assert(std::is_base_of < Goal<AgentType>, <GoalType>, "goal composite: subgoal must be..");
			auto& newGoal = mSubGoals.emplace_back(std::make_unique<GoalType>());
			return static_cast<GoalType*>(newGoal.get());

		}

		void RemoveAllSubGoals(AgentType& agent)
		{
			for (auto& goal : mSubGoals)
			{
				goal->Terminate(agent);
				goal.reset();
			}
		}

		Status ProcessSubGoal(AgentType& agent)
		{
			while (!mSubGoals.empty())
			{
				auto& goal = mSubGoals.back();
				if (goal->GetStatus() != Status::Completed && goal->GetStatus() != Status::Failed)
				{
					break;
				}
				goal->Terminate(agent);
				goal.reset();
				mSubGoals.pop_back();
			}
		}


		if (!mSubGoals.empty())
		{
			Status status = mSubGoals.back()->process(agent);	//////
			if (status)
			{

			}
		}

		std::vector<std::unique_ptr<Goal<AgentType>>> mSubGoals;

	};
}
