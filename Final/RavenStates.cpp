
#include "RavenStates.h"
#include <ImGui/Inc/ImGui.h>

void RavenGoHome::Enter(Raven& agent)
{
	agent.setTargetDestination(X::Math::Vector2(100, 100));
}

void RavenGoHome::Update(Raven& agent, float deltaTime)
{

	if (!agent.HasMineral())
	{
		agent.ChangeState(RavenState::GoToGatherSpot);
	}
	else if (agent.position.x <= 20 && agent.position.y <= 20)
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




void RavenGoToGatherSpot::Enter(Raven& agent)
{
	agent.setTargetDestination(X::Math::Vector2(500, 500));
}

void RavenGoToGatherSpot::Update(Raven& agent, float deltaTime)
{
	

}

void RavenGoToGatherSpot::Exit(Raven& agent)
{
}

void RavenGoToGatherSpot::DebugUI()
{
}



void RavenGoToMineral::Enter(Raven& agent)
{
}

void RavenGoToMineral::Update(Raven& agent, float deltaTime)
{
	/*if (agent.)
	{

	}*/

}

void RavenGoToMineral::Exit(Raven& agent)
{
}

void RavenGoToMineral::DebugUI()
{
}
