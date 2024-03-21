
#include "CrowStates.h"
#include <ImGui/Inc/ImGui.h>

void CrowGoHomeAndSleepUntilRestedState::Enter(Crow& agent)
{
	//agent.SetLocation(Location::Home);
}

void CrowGoHomeAndSleepUntilRestedState::Update(Crow& agent, float deltaTime)
{
	//agent.ResetFatigue();
	//if (agent.IsRested())
	//{
	//	if (!agent.IsWealthy())
	//	{
	//		agent.ChangeState(CrowState::EnterMineAndDigForNugget);
	//	}
	//	else
	//	{
	//		//done
	//	}
	//}
}

void CrowGoHomeAndSleepUntilRestedState::Exit(Crow& agent)
{

}

void CrowGoHomeAndSleepUntilRestedState::DebugUI()
{
	ImGui::Text("GoHomeAndSleepUntilRestedState: Crow is resting");
}

void CrowEnterMineAndDigForNuggetState::Enter(Crow& agent)
{
	//agent.SetLocation(Location::Mine);
}

void CrowEnterMineAndDigForNuggetState::Update(Crow& agent, float deltaTime)
{
	/*agent.IncreaseFatigue();
	agent.AddGoldCarried(1);
	if (agent.IsPocketFull())
	{
		agent.ChangeState(CrowState::VisitBankAndDepositGold);
	}
	else if (agent.IsThirsty())
	{
		agent.ChangeState(CrowState::QuenchThirst);
	}*/
}

void CrowEnterMineAndDigForNuggetState::Exit(Crow& agent)
{
}

void CrowEnterMineAndDigForNuggetState::DebugUI()
{
	ImGui::Text("EnterMineAndDigForNuggetState: Crow is digging for gold");
}

void CrowQuenchThirstState::Enter(Crow& agent)
{
	//agent.SetLocation(Location::Saloon);
}

void CrowQuenchThirstState::Update(Crow& agent, float deltaTime)
{
	/*agent.ResetThirst();
	if (!agent.IsThirsty())
	{
		agent.ChangeState(CrowState::EnterMineAndDigForNugget);
	}*/
}

void CrowQuenchThirstState::Exit(Crow& agent)
{
}

void CrowQuenchThirstState::DebugUI()
{
	ImGui::Text("QuenchThirstState: Crow is drinking");
}

void CrowVisitBankAndDepositGoldState::Enter(Crow& agent)
{
	//agent.SetLocation(Location::Bank);
}

void CrowVisitBankAndDepositGoldState::Update(Crow& agent, float deltaTime)
{
	/*agent.AddGoldToBank();
	if (!agent.IsRested())
	{
		agent.ChangeState(CrowState::GoHomeAndSleepTillRested);
	}
	else
	{
		agent.ChangeState(CrowState::EnterMineAndDigForNugget);
	}*/
}

void CrowVisitBankAndDepositGoldState::Exit(Crow& agent)
{
}

void CrowVisitBankAndDepositGoldState::DebugUI()
{
	//ImGui::Text("VisitBankAndDepositGoldState: Crow is depositing gold in the bank");
}
