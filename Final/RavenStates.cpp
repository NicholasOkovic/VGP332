
#include "RavenStates.h"
#include <ImGui/Inc/ImGui.h>

void GoHomeAndSleepUntilRestedState::Enter(Raven& agent)
{
	//agent.SetLocation(Location::Home);
}

void GoHomeAndSleepUntilRestedState::Update(Raven& agent, float deltaTime)
{
	//agent.ResetFatigue();
	//if (agent.IsRested())
	//{
	//	if (!agent.IsWealthy())
	//	{
	//		agent.ChangeState(RavenState::EnterMineAndDigForNugget);
	//	}
	//	else
	//	{
	//		//done
	//	}
	//}
}

void GoHomeAndSleepUntilRestedState::Exit(Raven& agent)
{

}

void GoHomeAndSleepUntilRestedState::DebugUI()
{
	//ImGui::Text("GoHomeAndSleepUntilRestedState: Raven is resting");
}

void EnterMineAndDigForNuggetState::Enter(Raven& agent)
{
	//agent.SetLocation(Location::Mine);
}

void EnterMineAndDigForNuggetState::Update(Raven& agent, float deltaTime)
{
	/*agent.IncreaseFatigue();
	agent.AddGoldCarried(1);
	if (agent.IsPocketFull())
	{
		agent.ChangeState(RavenState::VisitBankAndDepositGold);
	}
	else if (agent.IsThirsty())
	{
		agent.ChangeState(RavenState::QuenchThirst);
	}*/
}

void EnterMineAndDigForNuggetState::Exit(Raven& agent)
{
}

void EnterMineAndDigForNuggetState::DebugUI()
{
	//ImGui::Text("EnterMineAndDigForNuggetState: Raven is digging for gold");
}

void QuenchThirstState::Enter(Raven& agent)
{
	//agent.SetLocation(Location::Saloon);
}

void QuenchThirstState::Update(Raven& agent, float deltaTime)
{
	/*agent.ResetThirst();
	if (!agent.IsThirsty())
	{
		agent.ChangeState(RavenState::EnterMineAndDigForNugget);
	}*/
}

void QuenchThirstState::Exit(Raven& agent)
{
}

void QuenchThirstState::DebugUI()
{
	//ImGui::Text("QuenchThirstState: Raven is drinking");
}

void VisitBankAndDepositGoldState::Enter(Raven& agent)
{
	//agent.SetLocation(Location::Bank);
}

void VisitBankAndDepositGoldState::Update(Raven& agent, float deltaTime)
{
	/*agent.AddGoldToBank();
	if (!agent.IsRested())
	{
		agent.ChangeState(RavenState::GoHomeAndSleepTillRested);
	}
	else
	{
		agent.ChangeState(RavenState::EnterMineAndDigForNugget);
	}*/
}

void VisitBankAndDepositGoldState::Exit(Raven& agent)
{
}

void VisitBankAndDepositGoldState::DebugUI()
{
	//ImGui::Text("VisitBankAndDepositGoldState: Raven is depositing gold in the bank");
}
