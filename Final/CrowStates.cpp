
#include "CrowStates.h"
#include <ImGui/Inc/ImGui.h>

void CrowGoHome::Enter(Crow& agent)
{
	const float screenWidth = X::GetScreenWidth();
	const float screenHeight = X::GetScreenHeight();

	//agent.setTargetDestination(X::Math::Vector2(screenWidth - 250.0f, screenHeight / 1.2f));	///maybe add strat so no need to write stuff here except ifs
}

void CrowGoHome::Update(Crow& agent, float deltaTime)
{
	if (!agent.HasMineral())
	{
		agent.ChangeState(CrowState::Wander);
	}
	else if (agent.position.x >= 900 && agent.position.y >= 600)			///needs to be changed, maybe wrong pos
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

void CrowChaseRaven::Update(Crow& agent, float deltaTime)		//create strat for 
{

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




void CrowWander::Enter(Crow& agent)
{
}

void CrowWander::Update(Crow& agent, float deltaTime)
{
	if (agent.HasMineral())
	{
		agent.ChangeState(CrowState::GoHome);
	}
}

void CrowWander::Exit(Crow& agent)
{
}

void CrowWander::DebugUI()
{
}
