#include "pch.h"
#include "EnemyMissile.h"

EnemyMissile::EnemyMissile()
{

}

EnemyMissile::~EnemyMissile()
{

}

void EnemyMissile::BeginPlay()
{
	Super::BeginPlay();

	startPos = GetPos();
}

void EnemyMissile::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	ClientTimeSinceUpdate += deltaTime;
	//printf("EnemyM : %d \n", ClientTimeBetweenLastUpdate); 
	if (ClientTimeBetweenLastUpdate < UE_KINDA_SMALL_NUMBER)
	{
		return;
	}
	const Vec2 EstimateLocation = GetServerNewLocation() + (dir * speed * ClientTimeBetweenLastUpdate);
	const float LerpRatio = ClientTimeSinceUpdate / ClientTimeBetweenLastUpdate;

	float ClientNewX = lerp(GetServerNewLocation().x, EstimateLocation.x, LerpRatio);
	float ClientNewY = lerp(GetServerNewLocation().y, EstimateLocation.y, LerpRatio);
	const Vec2 ClientNewLoc = Vec2(ClientNewX, ClientNewY);
	SetPos(ClientNewLoc);

	/*Vec2 P0 = GetPos();
	Vec2 vt = dir * speed * deltaTime;
	Vec2 P = P0 + vt;
	SetPos(P);*/

}

void EnemyMissile::Render(HDC hdc)
{
	Super::Render(hdc);
}