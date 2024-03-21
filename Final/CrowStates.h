#pragma once

#include <AI.h>
#include "Crow.h"

class CrowGoHome : public AI::State<Crow>
{
public:
	void Enter(Crow& agent) override;
	void Update(Crow& agent, float deltaTime) override;
	void Exit(Crow& agent) override;
	void DebugUI() override;
private:

};

class CrowChaseRaven : public AI::State<Crow>
{
public:
	void Enter(Crow& agent) override;
	void Update(Crow& agent, float deltaTime) override;
	void Exit(Crow& agent) override;
	void DebugUI() override;
private:

};

class CrowDeposite : public AI::State<Crow>
{
public:
	void Enter(Crow& agent) override;
	void Update(Crow& agent, float deltaTime) override;
	void Exit(Crow& agent) override;
	void DebugUI() override;
private:

};
class CrowWander : public AI::State<Crow>
{
public:
	void Enter(Crow& agent) override;
	void Update(Crow& agent, float deltaTime) override;
	void Exit(Crow& agent) override;
	void DebugUI() override;
private:

};
