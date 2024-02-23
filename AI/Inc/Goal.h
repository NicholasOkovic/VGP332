#pragma once

namespace AI
{
	template<class AgentType>
	class Goal
	{
	public:
		enum class Status
		{
			Inactive,
			Active,
			Completed,
			Failed
		};
		Goal() = default;
		virtual ~Goal() = default;


		virtual void Activate(AgentType& agent) = 0;
		virtual Status Process(AgentType& agent) = 0;
		virtual void Terminate(AgentType& agent) = 0;

		Status GetState() const { return mStatus; }


	protected:
		void ActivateIfInactive(AgentType& agent)
		{
			if (mStatus == Status::Inactive)
			{
				Activate(agent)
			}
		}
		void ReactivateIfInactive(AgentType& agent)
		{
			if (mStatus == Status::Failed)
			{
				Activate(agent)
			}
		}

		Status mStatus = Status::Inactive;

	};
}