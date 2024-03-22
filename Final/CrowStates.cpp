
#include "CrowStates.h"
#include "TypeId.h"
#include <ImGui/Inc/ImGui.h>

void CrowGoHome::Enter(Crow& agent)
{
}

void CrowGoHome::Update(Crow& agent, float deltaTime)
{
	if (!agent.HasMineral())
	{
		agent.ChangeState(CrowState::Wander);
	}
	else if (agent.position.x >= 1160.0f && agent.position.y >= 590.0f)			
	{
		agent.ChangeState(CrowState::Deposite);
	}
}

void CrowGoHome::Exit(Crow& agent)
{
}

void CrowGoHome::DebugUI()
{
}



void CrowChaseRaven::Enter(Crow& agent)
{
}

void CrowChaseRaven::Update(Crow& agent, float deltaTime)		
{

	float distToTarget = X::Math::Magnitude(agent.position - agent.GetTargetDestination());

	if (distToTarget <= 25.0f)		//if agent is in range of Raven
	{
		agent.ChangeState(CrowState::Steal);
	}
}

void CrowChaseRaven::Exit(Crow& agent)
{
}

void CrowChaseRaven::DebugUI()
{
}



void CrowDeposite::Enter(Crow& agent)
{
}

void CrowDeposite::Update(Crow& agent, float deltaTime)
{
	if (!agent.HasMineral())
	{
		agent.ChangeState(CrowState::Wander);
	}
}

void CrowDeposite::Exit(Crow& agent)
{
}

void CrowDeposite::DebugUI()
{
}



void CrowWander::SetPerception(const AI::PerceptionModule* perception)
{
	mPerception = perception;
}

void CrowWander::Enter(Crow& agent)
{
	SetPerception(agent.GetPerception());
}

void CrowWander::Update(Crow& agent, float deltaTime)
{
	if (agent.HasMineral())
	{
		agent.ChangeState(CrowState::GoHome);
	}

	const auto& memoryRecords = mPerception->GetMemoryRecords();
	for (auto& record : memoryRecords)
	{
		AgentType agentType = static_cast<AgentType>(record.GetProperty<int>("type", 0));
		if (agentType == AgentType::Raven)
		{
			agent.ChangeState(CrowState::ChaseRaven);
		}
	}


}

void CrowWander::Exit(Crow& agent)
{
}

void CrowWander::DebugUI()
{
}



void CrowSteal::Enter(Crow& agent)
{
}

void CrowSteal::Update(Crow& agent, float deltaTime)
{
	float distToTarget = X::Math::Magnitude(agent.position - agent.GetTargetDestination());
	if (agent.HasMineral())
	{
		agent.ChangeState(CrowState::GoHome);
	}
	else if (distToTarget >= 30.0f)
	{
		agent.ChangeState(CrowState::Wander);
	}
}

void CrowSteal::Exit(Crow& agent)
{
}

void CrowSteal::DebugUI()
{
}


