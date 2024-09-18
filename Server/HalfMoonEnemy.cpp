#include "pch.h"
#include "HalfMoonEnemy.h"
#include "GameRoom.h"
#include "Player.h"
#include "ServerUtils.h"
#include "SeverTimeManager.h"
#include "SBoxCollider.h"
#include "SCollisionManager.h"
#include "SEnemyMissile.h"

void HalfMoonEnemy::Update()
{
	Super::Update();
	float deltaTime = GET_SINGLE(SeverTimeManager)->GetDeltaTime();
	if(deltaTime > 0.1) return;

	fireDelayCurrTime += deltaTime;
	if (fireDelayCurrTime > fireDelayTime) {
		fireDelayCurrTime = 0;
		FindPlayer();
		Fire();
	}
}

void HalfMoonEnemy::Fire()
{
	if(target == nullptr) return;
	Vector dir = target->GetPos() - GetPos();
	dir.Normalize();

	Vector spawnPos = Vector(enemyInfo.posx(), enemyInfo.posy());
	
	EnemyMissileRef missileRef = Actor::CreateEnemyMissile(spawnPos, dir);
	{
		shared_ptr<SBoxCollider> collider = make_shared<SBoxCollider>();
		collider->SetSize(Vector(17, 17)); //Enemy Missile Sprite Pixel Size
		GET_SINGLE(SCollisionManager)->AddCollider(collider);
		missileRef->AddComponent(collider);
	}
	GRoom->AddObject(missileRef);

	//Vec2 dir = target->GetPos() - GetPos();
	//dir.Normalize();

	//{
	//	Sprite* EnemyMissileSprite = GET_SINGLE(ResourceManager)->GetSprite(L"EnemyMissile");

	//	EnemyMissile* enemyMissile = new EnemyMissile();
	//	enemyMissile->SetPos(_pos);
	//	enemyMissile->SetSprite(EnemyMissileSprite);
	//	enemyMissile->SetLayer(LAYER_EnemyMissile);
	//	enemyMissile->SetDir(dir);
	//	Vec2Int SpriteSize = EnemyMissileSprite->GetSize();
	//	/*{
	//		BoxCollider* collider = new BoxCollider();
	//		collider->SetShowDebug(true);
	//		collider->SetSize(Vec2(SpriteSize.x, SpriteSize.y));
	//		collider->SetCollisionLayer(CLT_ENEMY_MISSILE);
	//		GET_SINGLE(CollisionManager)->AddCollider(collider);
	//		enemyMissile->AddComponent(collider);
	//	} */
	//	GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(enemyMissile);
	//}
}

//HalfMoonEnemy::HalfMoonEnemy(const Enemy& enemy)
//{
//
//}

void HalfMoonEnemy::FindPlayer()
{ 
	auto playerArr = GRoom->GetPlayerArr();

	vector<int> p;
	for (auto it = playerArr.begin(); it != playerArr.end(); ++it) {
		p.push_back(it->first);
	}
	if (playerArr.size() == 2) {
		int ranVal = ServerUtils::RandomIntegerRange(0, 1);
		target = static_pointer_cast<Player>(playerArr[p[ranVal]]);
	}
	else if (playerArr.size() == 1) {
		target = static_pointer_cast<Player>(playerArr[p[0]]);
	}
}

//void HalfMoonEnemy::Damaged()
//{
//	int currHp = GetHp();
//	SetHp(--currHp);
//
//	Super::Damaged();
//	/*bDamaged = true;
//	SetDamagedSprite();*/
//}