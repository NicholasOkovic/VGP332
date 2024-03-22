
#include "RavenStates.h"
#include "TypeId.h"
//#include "Mineral.h"
#include <ImGui/Inc/ImGui.h>

void RavenGoHome::Enter(Raven& agent)
{
	
}

void RavenGoHome::Update(Raven& agent, float deltaTime)
{

	if (!agent.HasMineral())
	{
		agent.ChangeState(RavenState::GoToGatherSpot);
	}
	else if (agent.position.x <= 120 && agent.position.y <= 120)
	{
		agent.ChangeState(RavenState::Deposite);
	}

	

}

void RavenGoHome::Exit(Raven& agent)
{
}

void RavenGoHome::DebugUI()
{
}



void RavenHarvestMineral::Enter(Raven& agent)
{
}

void RavenHarvestMineral::Update(Raven& agent, float deltaTime)
{
	if (agent.HasMineral())
	{
		agent.ChangeState(RavenState::GoHome);
	}
	//maybe make a timer for how long they can stay trying to get the mienral that was stolen
}

void RavenHarvestMineral::Exit(Raven& agent)
{
}

void RavenHarvestMineral::DebugUI()
{
}




void RavenDeposite::Enter(Raven& agent)
{
}

void RavenDeposite::Update(Raven& agent, float deltaTime)
{
	if (!agent.HasMineral())
	{
		agent.ChangeState(RavenState::GoToGatherSpot);
	}

}

void RavenDeposite::Exit(Raven& agent)
{
}

void RavenDeposite::DebugUI()
{
}


void RavenGoToGatherSpot::SetPerception(const AI::PerceptionModule* perception)
{
	mPerception = perception;
}

void RavenGoToGatherSpot::Enter(Raven& agent)
{
	SetPerception(agent.GetPerception());
}

void RavenGoToGatherSpot::Update(Raven& agent, float deltaTime)
{
	const auto& memoryRecords = mPerception->GetMemoryRecords();
	for (auto& record : memoryRecords)
	{
		AgentType agentType = static_cast<AgentType>(record.GetProperty<int>("type", 0));
		if (agentType == AgentType::Mineral)
		{
			agent.ChangeState(RavenState::GoToMineral);
		}
	}
	
}

void RavenGoToGatherSpot::Exit(Raven& agent)
{
}

void RavenGoToGatherSpot::DebugUI()
{
}


void RavenGoToMineral::SetPerception(const AI::PerceptionModule* perception)
{
	mPerception = perception;
}

void RavenGoToMineral::Enter(Raven& agent)
{
}

void RavenGoToMineral::Update(Raven& agent, float deltaTime)
{
	//change to ravenharvestmineral
	//Mineral* mineral = nullptr;
	//AI::EntityPtrs minerals = agent.world.GetEntitiesInRange({ agent.destination, 1.0f }, static_cast<uint32_t>(AgentType::Mineral));
	
	float distToTarget = X::Math::Magnitude(agent.position - agent.GetTargetDestination());

	if (distToTarget <= 20.0f)		//if agent is in range of mineral
	{
		agent.ChangeState(RavenState::HarvestMineral);
	}

}

void RavenGoToMineral::Exit(Raven& agent)
{
}

void RavenGoToMineral::DebugUI()
{
}

//void RavenNoStrat::Enter(Raven& agent)
//{
//}
//
//void RavenNoStrat::Update(Raven& agent, float deltaTime)
//{
//	/*if (!agent.HasMineral())
//	{
//		agent.ChangeState(RavenState::GoToGatherSpot);
//	}
//	else
//	{
//		agent.ChangeState(RavenState::GoHome);
//	}*/
//
//}
//
//void RavenNoStrat::Exit(Raven& agent)
//{
//}
//
//void RavenNoStrat::DebugUI()
//{
//}
