#include "PersonStates.h"
#include <ImGui/Inc/ImGui.h>

void GoHomeAndSleepState::Enter(Person& agent)
{
	agent.SetLocation(Location::Home);
}

void GoHomeAndSleepState::Update(Person& agent, float deltaTime)
{
	agent.ResetDay();
	if (!agent.IsDayOver())
	{
		if (agent.IsRentDue())
		{
			agent.SpendMoney(500);
		}
		else if (!agent.IsWealthy())
		{
			agent.ChangeState(PersonState::StartWorking);
		}
		else
		{
			//done
		}
	}
}

void GoHomeAndSleepState::Exit(Person& agent)
{
}

void GoHomeAndSleepState::DebugUI()
{
	ImGui::Text("Sleeping");
}

void StartWorkingState::Enter(Person& agent)
{
	agent.SetLocation(Location::Work);
}

void StartWorkingState::Update(Person& agent, float deltaTime)
{
	if (agent.IsDayOver())
	{
		agent.ChangeState(PersonState::GoHomeAndSleep);
	}
	else if (agent.IsThirsty())
	{
		agent.ChangeState(PersonState::Drink);
	}
	else if (agent.IsHungry())
	{
		agent.ChangeState(PersonState::Eat);
	}
	agent.TimePassed();
	agent.AddMoney(10);
}

void StartWorkingState::Exit(Person& agent)
{
}

void StartWorkingState::DebugUI()
{
	ImGui::Text("Working");
}

void DrinkState::Enter(Person& agent)
{
	agent.SetLocation(Location::Starbucks);
}

void DrinkState::Update(Person& agent, float deltaTime)
{
	agent.ResetThirst();
	agent.SpendMoney(3);
	agent.TimePassed();
	if (!agent.IsThirsty())
	{
		if (agent.IsHungry())
		{
			agent.ChangeState(PersonState::Eat);
		}
		agent.ChangeState(PersonState::StartWorking);
	}
}

void DrinkState::Exit(Person& agent)
{
}

void DrinkState::DebugUI()
{
	ImGui::Text("Drinking");
}

void EatState::Enter(Person& agent)
{
	agent.SetLocation(Location::Restaurant);
}

void EatState::Update(Person& agent, float deltaTime)
{
	agent.ResetHunger();
	agent.SpendMoney(5);
	agent.TimePassed();
	if (!agent.IsHungry())
	{
		if (agent.IsThirsty())
		{
			agent.ChangeState(PersonState::Drink);
		}
		agent.ChangeState(PersonState::StartWorking);
	}
}

void EatState::Exit(Person& agent)
{
}

void EatState::DebugUI()
{
	ImGui::Text("Eating");
}
