#include "Game.h"

#include "../Engine/ECS/Component/Embedded/Mesh.h"
#include "../Engine/ECS/Component/Embedded/Text.h"
#include "../Engine/ECS/Component/Embedded/Velocity.h"
#include "../Engine/ECS/System/Embedded/InertiaSystem.h"
#include "../Engine/ECS/System/Embedded/MeshRenderSystem.h"
#include "../Engine/ECS/System/Embedded/MoveSystem.h"
#include "../Engine/ECS/System/Embedded/TextRenderSystem.h"
#include "../Engine/Math.h"
#include "../Engine/Scene.h"
#include "../Engine/Types/Vector2.h"
#include "Components/Blast.h"
#include "Components/Collider/ColliderLethal.h"
#include "Components/Collider/ColliderTarget.h"
#include "Components/Enemy.h"
#include "Components/GravityBigObject.h"
#include "Components/GravitySmallObject.h"
#include "Components/JetStreamParticles.h"
#include "Components/LifeTime.h"
#include "Components/Projectile.h"
#include "Components/ProjectileLauncher.h"
#include "Components/Rotor.h"
#include "Components/User.h"
#include "Systems/UnitSystems/UserInputSystem.h"
#include "Systems/BlastSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/EndOfGameSystem.h"
#include "Systems/GravitySystem.h"
#include "Systems/RotorSystem.h"
#include "Systems/StarRenderSystem.h"
#include "Systems/JetStreamSystem.h"
#include "Systems/LifeTimeSystem.h"
#include "Systems/UnitSystems/EnemySystem.h"

Text* Game::_endOfGameText = nullptr;

Ship Game::_userShip = {
	{{-Scene::scale.x * 0.75f, -Scene::scale.y * 0.75f}, Math::DegreeToRad(45.f)},
	nullptr
};

std::vector<Ship> Game::_enemyShips = {
	{{{Scene::scale.x * 0.25f, Scene::scale.y * 0.75f}, Math::DegreeToRad(-125.f)},
	nullptr},
	{{{Scene::scale.x * 0.75f, Scene::scale.y * 0.75f}, Math::DegreeToRad(-135.f)},
	nullptr},
	{{{Scene::scale.x * 0.75f, Scene::scale.y * 0.25f}, Math::DegreeToRad(-145.f)},
	nullptr}
};

void Game::Init()
{
	const int userColliderTag = 1;
	
	_userShip.ShipEntity = CreateWedge(_userShip.InitialTransform, userColliderTag);

	for (auto&& enemy : _enemyShips)
	{
		enemy.ShipEntity = CreateNeedle(enemy.InitialTransform);
	}
	
	CreateGravityWell();

	// not a separate pool, it's inside ECS
	CreateProjectilePool(30);
	
	auto text = Scene::GetEntityManager().Create();
	_endOfGameText = text->AddComponent<Text>();
	_endOfGameText->enabled = false;	
	
	Scene::GetSystemManager().Create<UserInputSystem>(1);
	Scene::GetSystemManager().Create<EnemySystem>(1);
	
	Scene::GetSystemManager().Create<MoveSystem>(1);
	Scene::GetSystemManager().Create<InertiaSystem>(1);

	Scene::GetSystemManager().Create<RotorSystem>(1);
	Scene::GetSystemManager().Create<GravitySystem>(1);
	Scene::GetSystemManager().Create<CollisionSystem>(1);
	Scene::GetSystemManager().Create<BlastSystem>(1);
		
	Scene::GetSystemManager().Create<EndOfGameSystem>(2, userColliderTag, EndGame);
	Scene::GetSystemManager().Create<LifeTimeSystem>(2);
	
	Scene::GetSystemManager().Create<StarRenderSystem>(10, Color3{ 0.8f, 0.9f, 1 });
	Scene::GetSystemManager().Create<MeshRenderSystem>(10);
	Scene::GetSystemManager().Create<JetStreamSystem>(10, 0.05f);
	Scene::GetSystemManager().Create<TextRenderSystem>(10);
}

void Game::Reset()
{
	_userShip.ShipEntity->transform = _userShip.InitialTransform;
	_userShip.ShipEntity->GetComponent<Velocity>()->value = Vector2::ZERO;
	_userShip.ShipEntity->GetComponent<ColliderTarget>()->isHit = false;
	_userShip.ShipEntity->GetComponent<Blast>()->isBlasted = false;
	_userShip.ShipEntity->enabled = true;

	for (auto&& enemy : _enemyShips)
	{
		enemy.ShipEntity->transform = enemy.InitialTransform;
		enemy.ShipEntity->GetComponent<Velocity>()->value = Vector2::ZERO;
		enemy.ShipEntity->GetComponent<ColliderTarget>()->isHit = false;
		enemy.ShipEntity->GetComponent<Blast>()->isBlasted = false;
		enemy.ShipEntity->enabled = true;
	}

	auto times = Scene::GetComponentManager().FindAllComponents<LifeTime>();

	LifeTime* time = nullptr;

	// end tine of all LifeTime objects
	while (times.Next(time, true))
	{
		time->timeNow = time->timeMax;
	}
	
	_endOfGameText->enabled = false;
}

Entity* Game::CreateWedge(const Transform& transform, int userColliderTag)
{
	auto wedge = Scene::GetEntityManager().Create(transform);

	wedge->AddComponent<Velocity>()->drag = 0.85f;

	auto mesh = wedge->AddComponent<Mesh>();

	std::vector<Vector2> triangles = {
		{0, 0.1f},
		{-0.1f, -0.1f},
		{0.1f, -0.1f}
	};

	mesh->SetTriangles(std::move(triangles));

	auto blast = wedge->AddComponent<Blast>();

	blast->AddShard({0, 0.05f}, {
		{ 0, 0.1f },
		{ -0.05f, 0 },
		{ 0.05f, 0 }
	});

	blast->AddShard({ 0, -0.05f }, {
		{-0.05f, 0},
		{0.05f, 0},
		{0, -0.1f}
	});

	blast->AddShard({ -0.05f, -0.05f }, {
		{-0.05f, 0},
		{-0.1f, -0.1f},
		{0, -0.1f}
	});

	blast->AddShard({ 0.05f, -0.05f }, {
		{0.05f, 0},
		{0.1f, -0.1f},
		{0, -0.1f}
	});
	
	wedge->AddComponent<GravitySmallObject>();
	wedge->AddComponent<JetStreamParticles>();
	wedge->AddComponent<ColliderTarget>(0.2f, userColliderTag);
	wedge->AddComponent<ProjectileLauncher>();
	wedge->AddComponent<User>();

	return wedge;
}

Entity* Game::CreateNeedle(const Transform& transform)
{
	auto needle = Scene::GetEntityManager().Create(transform);

	needle->AddComponent<Velocity>()->drag = 0.75f;

	auto mesh = needle->AddComponent<Mesh>();

	std::vector<Vector2> triangles = {
		// head
		{0, 0.1f},
		{-0.02f, 0.06f},
		{0.02f, 0.06f},

		{-0.02f, 0.06f},
		{-0.02f, -0.04f},
		{0.02f, 0.06f},

		{0.02f, 0.06f},
		{-0.02f, -0.04f},
		{0.02f, -0.04f},

		// center
		{-0.02f, -0.04f},
		{0, -0.11f},
		{0.02f, -0.04f},

		{-0.02f, -0.04f},
		{-0.02f, -0.15f},
		{0, -0.11f},

		{0.02f, -0.04f},
		{0.02f, -0.15f},
		{0, -0.11f},

		// sides
		{-0.02f, -0.04f},
		{-0.04f, -0.09f},
		{-0.02f, -0.15f},

		{0.02f, -0.04f},
		{0.04f, -0.09f},
		{0.02f, -0.15f},

		{-0.04f, -0.09f},
		{-0.04f, -0.15f},
		{-0.02f, -0.15f},

		{0.04f, -0.09f},
		{0.04f, -0.15f},
		{0.02f, -0.15f}
	};

	mesh->SetTriangles(std::move(triangles));

	auto blast = needle->AddComponent<Blast>();

	blast->AddShard({0, -0.07f}, {
		{0, 0.1f},
		{-0.02f, 0.06f},
		{0.02f, 0.06f},

		{-0.02f, 0.06f},
		{-0.02f, -0.04f},
		{0.02f, 0.06f},

		{0.02f, 0.06f},
		{-0.02f, -0.04f},
		{0.02f, -0.04f}
	});

	blast->AddShard({ 0, -0.055f }, {
		{-0.02f, -0.04f},
		{0, -0.11f},
		{0.02f, -0.04f},

		{-0.02f, -0.04f},
		{-0.02f, -0.15f},
		{0, -0.11f},

		{0.02f, -0.04f},
		{0.02f, -0.15f},
		{0, -0.11f}
	});

	blast->AddShard({ -0.03f, -0.055f }, {
		{-0.02f, -0.04f},
		{-0.04f, -0.09f},
		{-0.02f, -0.15f},

		{-0.04f, -0.09f},
		{-0.04f, -0.15f},
		{-0.02f, -0.15f}
	});

	blast->AddShard({ 0.03f, -0.055f }, {

		{0.02f, -0.04f},
		{0.04f, -0.09f},
		{0.02f, -0.15f},
		
		{0.04f, -0.09f},
		{0.04f, -0.15f},
		{0.02f, -0.15f}
	});

	needle->AddComponent<GravitySmallObject>();
	needle->AddComponent<JetStreamParticles>();
	needle->AddComponent<ColliderTarget>(0.2f, 2);
	needle->AddComponent<ProjectileLauncher>()->coolDown = 1.5f;
	needle->AddComponent<Enemy>();

	return needle;
}

void Game::CreateGravityWell()
{
	auto gravityWell = Scene::GetEntityManager().Create();

	auto gravityWellMesh = gravityWell->AddComponent<Mesh>();

	std::vector<Vector2> gravityWellLines = {
		{0, 0},
		{0, 0.1f},
		{0, 0},
		{0, -0.1f},
		{0, 0},
		{-0.1f, 0},
		{0, 0},
		{0.1f, 0},

		{0, 0},
		{0.07f, 0.07f},
		{0, 0},
		{-0.07f, 0.07f},
		{0, 0},
		{0.07f, -0.07f},
		{0, 0},
		{-0.07f, -0.07f},
	};

	gravityWellMesh->SetLines(std::move(gravityWellLines));

	gravityWell->AddComponent<Rotor>(1.5f);
	gravityWell->AddComponent<GravityBigObject>(0.07f, 1.8f);
	gravityWell->AddComponent<ColliderLethal>(0.2f, 0);
}

void Game::CreateProjectilePool(int size)
{
	for (auto i = 0; i < size; i++)
	{
		auto projectile = Scene::GetEntityManager().Create();
		projectile->enabled = false;
		
		auto mesh = projectile->AddComponent<Mesh>();

		std::vector<Vector2> triangles = {
			{0, 0.1f},
			{-0.01f, 0.06f},
			{0.01f, 0.06f},

			{-0.01f, 0.06f},
			{-0.01f, -0.05f},
			{0.01f, 0.06f},

			{0.01f, 0.06f},
			{-0.01f, -0.05f},
			{0.01f, -0.05f},
		};

		mesh->SetTriangles(std::move(triangles));

		projectile->AddComponent<Projectile>()->impulse = 1.2f;
		projectile->AddComponent<ColliderLethal>(0.1f, 0);		
		projectile->AddComponent<Velocity>()->drag = 0;
		projectile->AddComponent<LifeTime>(5.f)->isDisposable = false;
	}
}

void Game::EndGame(bool isWin)
{
	_endOfGameText->enabled = true;

	if (isWin)
	{
		_endOfGameText->GetEntity()->transform.position = {-0.18f, 0.12f};
		_endOfGameText->value = "WIN";
	}
	else
	{
		_endOfGameText->GetEntity()->transform.position = { -0.23f, 0.12f };
		_endOfGameText->value = "FAIL";
	}
}
