#include "TileMap.h"
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <ImGui/Inc/imgui.h>


#include "SCV.h"
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
int startX = 9;
int startY = 10;
int endX = 18; //13
int endY = 18; //15


float wanderJitter = 5.0f;
float wanderRadius = 20.0f;
float wanderDistance = 50.0f;
float radius = 50.0f;


float viewRange = 300.0f;
float viewAngle = 45.0f;





AIWorld aiWorld;
std::vector<std::unique_ptr<Raven>> ravenAgents;
std::vector<std::unique_ptr<Crow>> crowAgents;
std::vector<std::unique_ptr<SCV>> scvAgents;
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

	agent->position = X::RandomVector2({ 80.0f, 80.0f },
		{ 120.0f, 120.0f });
	agent->destination = destination;
	agent->radius = radius;
	agent->ShowDebug(showDebug);
	agent->SetSeek(useSeek);
	//agent->SetWander(useWander);

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




	textureId = X::LoadTexture("bird1.png");
	position = { 100.0f, 100.0f };
}

bool GameLoop(float deltaTime)
{
	const float moveSpeed = 200.0f; // pixel per second
	if (X::IsKeyDown(X::Keys::RIGHT))
		position.x += moveSpeed * deltaTime;
	else if (X::IsKeyDown(X::Keys::LEFT))
		position.x -= moveSpeed * deltaTime;
	if (X::IsKeyDown(X::Keys::DOWN))
		position.y += moveSpeed * deltaTime;
	else if (X::IsKeyDown(X::Keys::UP))
		position.y -= moveSpeed * deltaTime;

	ImGui::Begin("PathFinding", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{
		const int columns = tileMap.GetColumns();
		const int rows = tileMap.GetRows();
		ImGui::DragInt("StartX", &startX, 1, 0, columns - 1);
		ImGui::DragInt("StartY", &startY, 1, 0, rows - 1);
		ImGui::DragInt("EndX", &endX, 1, 0, columns - 1);
		ImGui::DragInt("EndY", &endY, 1, 0, rows - 1);
		if (ImGui::Button("RunBFS"))
		{
			path = tileMap.FindPathBFS(startX, startY, endX, endY);
		}
		if (ImGui::Button("RunDFS"))
		{
			path = tileMap.FindPathDFS(startX, startY, endX, endY);
		}
		if (ImGui::Button("RunDijkstra"))
		{
			path = tileMap.FindPathDijkstra(startX, startY, endX, endY);
		}
		if (ImGui::Button("RunAStar"))
		{
			path = tileMap.FindPathAStar(startX, startY, endX, endY);
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
		
		if (ImGui::Button("SpawnCrow"))
		{
			SpawnCrow();
		}
		ImGui::SameLine();
		if (ImGui::Button("KillCrow") && !crowAgents.empty())
		{
			KillCrow();
		}

		if (ImGui::Checkbox("ShowDebug", &showDebug))
		{
			for (auto& agent : ravenAgents)
			{
				agent->ShowDebug(showDebug);		
			}
			for (auto& agent : crowAgents)
			{
				agent->ShowDebug(showDebug);		
			}
		}
		
	}
	ImGui::End();

	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		const float mouseX = static_cast<float>(X::GetMouseScreenX());
		const float mouseY = static_cast<float>(X::GetMouseScreenY());
		destination = { mouseX, mouseY };
		

		for (auto& agent : ravenAgents)
		{
			agent->setTargetDestination(destination);
		}
	}

	//rendering

	aiWorld.Update();

	tileMap.Render();

	X::DrawSprite(textureId, position, X::Pivot::TopLeft, X::Flip::Horizontal);
	X::DrawScreenDiamond(position, 5.0f, X::Colors::Cyan);

	for (int i = 1; i < path.size(); ++i)
	{
		X::DrawScreenLine(path[i - 1], path[i], X::Colors::Red);
	}
	X::DrawScreenCircle(tileMap.GetPixelPosition(startX, startY), 10.0f, X::Colors::Pink);
	X::DrawScreenCircle(tileMap.GetPixelPosition(endX, endY), 10.0f, X::Colors::Yellow);

	


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