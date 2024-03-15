
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <AI.h>
#include <ImGui/Inc/imgui.h>


#include "SCV.h"
#include "Mineral.h"
#include "Raven.h"


using namespace AI;

extern float viewRange;
extern float viewAngle;




//--------------------------------------------------
AIWorld aiWorld;
std::vector<std::unique_ptr<Raven>> ravenAgents;
std::vector<std::unique_ptr<SCV>> scvAgents;
std::vector<std::unique_ptr<Mineral>> minerals;

X::Math::Vector2 destination = X::Math::Vector2::Zero();

bool showDebug = false;
bool useSeek = false;
bool useFlee = false;
bool useArrive = false;
bool useWander = false;
bool usePursuit = false;
bool useSeperation = false;
bool useAlignment = false;
bool useCohesion = false;


float weightSeek = 1.0f;
float weightFlee = 1.0f;
float weightArrive = 1.0f;
float weightWander = 1.0f;
float weightPursuit = 1.0f;
float weightSeperation = 1.0f;
float weightAlignment = 1.0f;
float weightCohesion = 1.0f;

float wanderJitter = 5.0f;
float wanderRadius = 20.0f;
float wanderDistance = 50.0f;
float radius = 50.0f;


float viewRange = 300.0f;
float viewAngle = 45.0f;


void SpawnAgent()
{
	auto& agent = scvAgents.emplace_back(std::make_unique<SCV>(aiWorld));
	agent->Load();

	const float screenWidth = X::GetScreenWidth();
	const float screenHeight = X::GetScreenHeight();

	agent->position = X::RandomVector2({ 100.0f, 100.0f },
		{ screenWidth - 100.0f, screenHeight - 100.0f });
	agent->destination = destination;
	agent->radius = radius;
	agent->ShowDebug(showDebug);
	agent->SetSeek(useSeek);
	agent->SetWander(useWander);


}
void KillAgent()
{
	auto& agent = scvAgents.back();
	agent->Unload();

	scvAgents.pop_back();
}
void SpawnRaven()
{
	auto& agent = ravenAgents.emplace_back(std::make_unique<Raven>(aiWorld));
	agent->Load();

	const float screenWidth = X::GetScreenWidth();
	const float screenHeight = X::GetScreenHeight();

	agent->position = X::RandomVector2({ 100.0f, 100.0f },
		{ screenWidth - 100.0f, screenHeight - 100.0f });
	agent->destination = destination;
	agent->radius = radius;
	agent->ShowDebug(showDebug);
	agent->SetWander(useWander);


}
void KillRaven()
{
	auto& agent = ravenAgents.back();
	agent->Unload();

	ravenAgents.pop_back();
}


void GameInit()
{
	aiWorld.Initialize();

	for (uint32_t i = 0; i < 10; ++i)
	{
		auto& mineral = minerals.emplace_back(std::make_unique<Mineral>(aiWorld));
		mineral->Initialize();
	}

	aiWorld.AddObstacle({ 230.0f, 300.0f, 50.0f });

	X::Math::Vector2 topLeft(500.0f, 100.0f);
	X::Math::Vector2 topRight(600.0f, 100.0f);
	X::Math::Vector2 bottomLeft(500.0f, 600.0f);
	X::Math::Vector2 bottomRight(600.0f, 600.0f);
	aiWorld.AddWall({ topLeft, topRight });
	aiWorld.AddWall({ topRight, bottomRight });
	aiWorld.AddWall({ bottomLeft, bottomRight });
	aiWorld.AddWall({ bottomLeft, topLeft });


}

bool GameLoop(float deltaTime)
{


	ImGui::Begin("Steering", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{
		if (ImGui::Button("SpawnAgent"))
		{
			SpawnAgent();
		}
		ImGui::SameLine();
		if (ImGui::Button("KillAgent") && !scvAgents.empty())
		{
			KillAgent();
		}
		if (ImGui::Button("SpawnRaven"))
		{
			SpawnRaven();
		}
		ImGui::SameLine();
		if (ImGui::Button("KillRaven") && !ravenAgents.empty())
		{
			KillRaven();
		}
		if (ImGui::Checkbox("ShowDebug", &showDebug))
		{
			for (auto& agent : scvAgents)
			{
				agent->ShowDebug(showDebug);		
			}
			for (auto& agent : ravenAgents)
			{
				agent->ShowDebug(showDebug);		
			}
		}




		if (ImGui::Checkbox("seek", &useSeek))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetSeek(useSeek);
			}
			
		}
		ImGui::SameLine();
		if (ImGui::DragFloat("seekWeight", &weightSeek, 0.1f, 0.1f, 0.5f))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetSeekWeight(weightSeek);
			}
		}





		if (ImGui::Checkbox("Wander", &useWander))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetWander(useWander);
			}
			/*for (auto& agent : ravenAgents)
			{
				agent->SetWander(useWander);
			}*/
		}
		if (useWander)
		{
			if (ImGui::CollapsingHeader("WanderingSettings", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::DragFloat("Jitter", &wanderJitter, 0.1f, 0.1f, 10.0f);
				ImGui::DragFloat("Radius", &wanderRadius, 0.1f, 0.1f, 100.0f);
				ImGui::DragFloat("Distance", &wanderDistance, 0.1f, 0.1f, 500.0f);
			}
		}


		if (ImGui::CollapsingHeader("visualSensor", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::DragFloat("viewRange", &viewRange, 1.0f, 100.0f, 1000.0f);
			ImGui::DragFloat("viewAngle", &viewAngle, 1.0f, 1.0f, 180.0f);
			

		}
	}
	ImGui::End();

	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		const float mouseX = static_cast<float>(X::GetMouseScreenX());
		const float mouseY = static_cast<float>(X::GetMouseScreenY());
		destination = { mouseX, mouseY };

		for (auto& agent : scvAgents)
		{
			agent->destination = destination;
		}
		for (auto& agent : ravenAgents)
		{
			agent->setTargetDestination(destination);
		}
	}

	aiWorld.Update();

	for (auto& agent : scvAgents)
	{
		EntityPtrs neighbors = aiWorld.GetEntitiesInRange({ agent->position, 500.0f }, 0);
		agent->neighbors.clear();
		for (auto& n : neighbors)
		{
			if (n != agent.get())
			{
				agent->neighbors.push_back(static_cast<Agent*>(n));
			}
		}
	}



	for (auto& agent : scvAgents)
	{
		agent->Update(deltaTime);
	}
	for (auto& agent : ravenAgents)
	{
		agent->Update(deltaTime);
	}
	for (auto& agent : scvAgents)
	{
		agent->Render();
	}
	for (auto& agent : ravenAgents)
	{
		agent->Render();
	}
	
	auto iter = minerals.begin();
	while (iter != minerals.end())
	{
		if (iter->get()->GetHealth() == 0)
		{
			iter->reset();
			iter = minerals.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	for (auto& mineral : minerals)
	{
		mineral->Render();
	}

	const AIWorld::Obstacles& obstacles = aiWorld.GetObstacles();
	for (const X::Math::Circle& obstacle : obstacles)
	{
		X::DrawScreenCircle(obstacle.center, obstacle.radius, X::Colors::Gray);
	}
	const AIWorld::Walls& walls = aiWorld.GetWalls();
	for (const X::Math::LineSegment& wall : walls)
	{
		X::DrawScreenLine(wall.from, wall.to, X::Colors::Gray);
	}


	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	for (auto& agent : scvAgents)
	{
		agent->Unload();
		agent.reset();
	}
	for (auto& agent : ravenAgents)
	{
		agent->Unload();
		agent.reset();
	}
	for (auto& mineral : minerals)
	{
		mineral.reset();
	}
	ravenAgents.clear();
	scvAgents.clear();
	minerals.clear();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Steering");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}