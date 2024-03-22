#include "TileMap.h"
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <ImGui/Inc/imgui.h>



#include "Mineral.h"
#include "Raven.h"
#include "Crow.h"

using namespace AI;

extern float viewRange;
extern float viewAngle;


TileMap tileMap;
X::TextureId textureId;
X::Math::Vector2 position;
Path path;

float wanderJitter = 5.0f;
float wanderRadius = 20.0f;
float wanderDistance = 50.0f;
float radius = 50.0f;


float viewRange = 300.0f;
float viewAngle = 45.0f;

int ravenDeposites = 0;
int crowDeposites = 0;


AIWorld aiWorld;
std::vector<std::unique_ptr<Raven>> ravenAgents;
std::vector<std::unique_ptr<Crow>> crowAgents;
std::vector<std::unique_ptr<Mineral>> minerals;

X::Math::Vector2 destination = X::Math::Vector2::Zero();

//--------------------------------------------------

bool showDebug = false;
bool useSeek = false;
bool useWander = false;
bool useArrive = false;


void SpawnRaven()
{
	auto& agent = ravenAgents.emplace_back(std::make_unique<Raven>(aiWorld));
	agent->Load();

	const float screenWidth = X::GetScreenWidth();
	const float screenHeight = X::GetScreenHeight();

	agent->position = X::RandomVector2({ 120.0f, 120.0f },
		{ 150.0f, 150.0f });
	agent->destination = destination;
	agent->radius = radius;
	agent->ShowDebug(showDebug);
	agent->SetSeek(useSeek);

	agent->SetTileMap(&tileMap);

}
void KillRaven()
{
	auto& agent = ravenAgents.back();
	agent->Unload();

	ravenAgents.pop_back();
}

void SpawnCrow()
{
	auto& agent = crowAgents.emplace_back(std::make_unique<Crow>(aiWorld));
	agent->Load();
	
	const float screenWidth = X::GetScreenWidth();
	const float screenHeight = X::GetScreenHeight();



	agent->position = X::RandomVector2({ screenWidth - 250.0f,  screenHeight/ 1.2f },
		{ screenWidth - 100.0f, screenHeight /1.1f });
	


	agent->destination = destination;
	agent->radius = radius;
	agent->ShowDebug(showDebug);
	agent->SetSeek(useSeek);
	agent->SetWander(useWander);

	agent->SetTileMap(&tileMap);

}
void KillCrow()
{
	auto& agent = crowAgents.back();
	agent->Unload();

	crowAgents.pop_back();
}

void GameInit()
{
	aiWorld.Initialize();
	for (uint32_t i = 0; i < 10; ++i)
	{
		auto& mineral = minerals.emplace_back(std::make_unique<Mineral>(aiWorld));
		mineral->Initialize();
	}
	tileMap.LoadTiles("tiles.txt");
	tileMap.LoadMap("map.txt");
}

bool GameLoop(float deltaTime)
{




	ImGui::Begin("PathFinding", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{

		ImGui::Text("Raven Deposites: [%i]", ravenDeposites);
		ImGui::Text("Crow Deposites: [%i]", crowDeposites);

	//	if (ImGui::Button("SpawnRaven"))
	//	{
	//		SpawnRaven();
	//	}
	//	ImGui::SameLine();
	//	if (ImGui::Button("KillRaven") && !ravenAgents.empty())			//buttons
	//	{
	//		KillRaven();
	//	}
	//	
	//	if (ImGui::Button("SpawnCrow"))
	//	{
	//		SpawnCrow();
	//	}
	//	ImGui::SameLine();
	//	if (ImGui::Button("KillCrow") && !crowAgents.empty())
	//	{
	//		KillCrow();
	//	}

	//	if (ImGui::Checkbox("ShowDebug", &showDebug))
	//	{
	//		for (auto& agent : ravenAgents)
	//		{
	//			agent->ShowDebug(showDebug);		
	//		}
	//		for (auto& agent : crowAgents)
	//		{
	//			agent->ShowDebug(showDebug);		
	//		}
	//	}

		
	}
	ImGui::End();

	//rendering

	aiWorld.Update();

	tileMap.Render();

	//bases
	X::DrawScreenDiamond(110.0f, 110.0f, 10.0f, X::Colors::Cyan);
	X::DrawScreenDiamond(1168.0f, 625.0f, 10.0f, X::Colors::Azure);

	for (int i = 1; i < path.size(); ++i)
	{
		X::DrawScreenLine(path[i - 1], path[i], X::Colors::Red);
	}

	


	for (auto& agent : ravenAgents)
	{
		agent->Update(deltaTime);		
	}
	for (auto& agent : ravenAgents)
	{
		agent->Render();		
	}

	for (auto& agent : crowAgents)
	{
		agent->Update(deltaTime);
	}
	for (auto& agent : crowAgents)
	{
		agent->Render();
	}

	//auto iter = minerals.begin();
	//while (iter != minerals.end())
	//{
	//	if (iter->get()->GetHealth() == 0)		//removes mushrooms from scene
	//	{
	//		iter->reset();
	//		iter = minerals.erase(iter);
	//	}
	//	else
	//	{
	//		++iter;
	//	}
	//}
	for (auto& mineral : minerals)
	{
		mineral->Update(deltaTime);
	}
	for (auto& mineral : minerals)
	{
		mineral->Render();
	}


	if (ravenAgents.size() < 4)
	{
		SpawnRaven();
	}
	if (crowAgents.size() < 3)
	{
		SpawnCrow();
	}

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	for (auto& agent : ravenAgents)
	{
		agent->Unload();
		agent.reset();
	}
	for (auto& agent : crowAgents)
	{
		agent->Unload();
		agent.reset();
	}
	for (auto& mineral : minerals)
	{
		mineral.reset();
	}
	ravenAgents.clear();
	crowAgents.clear();
	minerals.clear();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Pathfinding");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}