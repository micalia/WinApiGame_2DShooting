#include "pch.h"
#include "Enemy.h"
#include "GameRoom.h"
#include "SeverTimeManager.h"
#include "SCollisionManager.h"
#include "SMissile.h"
#include "SCollider.h"
#include "Player.h"

Enemy::Enemy() 
{

}

Enemy::~Enemy() 
{

}

void Enemy::Damaged() {
	SetHp(--hp);
	if (GetHp() > 0 && room != nullptr) {
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_EnemyDamaged(enemyInfo);
		room->Broadcast(sendBuffer);
	}
}
void Enemy::Update()
{
	Super::Update();
	float deltaTime = GET_SINGLE(SeverTimeManager)->GetDeltaTime();
	if (deltaTime > 0.1f) return;

	Move(deltaTime);
	currReplicateDelay += deltaTime;
	if (currReplicateDelay > replicateDelay) {
		currReplicateDelay = 0;
		EnemyBroadcastMove();
	}
}

void Enemy::Die(shared_ptr<Player> WhoHitMe)
{
	//printf("Server Enemy Die! \n", );
	/*ExplosionEffect* explosionEffect = new ExplosionEffect();
	explosionEffect->SetPos(GetPos());
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(explosionEffect);
	GET_SINGLE(SceneManager)->GetCurrentScene()->RemoveActor(this);
	_dirtyFlag = true;

	Server_AddScore(WhoHitMe, GetKillScore());*/
}

void Enemy::EnemyBroadcastMove()
{
	if (room)
	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_EnemyMove(enemyInfo);
		room->Broadcast(sendBuffer);
	}
}

void Enemy::SetEnemyPos(Vector pos)
{
	enemyInfo.set_posx(pos.x);
	enemyInfo.set_posy(pos.y);

	EnemyBroadcastMove();
}

void Enemy::SetEnemyInfo(EnemyRef InEnemy, Vector InSpawnPos, Protocol::EnemyType InEnemyType, float InSpeed)
{
	info.set_objectid(s_idGenerator++);
	enemyInfo.set_enemytype(InEnemyType);
	info.set_posx(InSpawnPos.x);
	info.set_posy(InSpawnPos.y);
	enemyInfo.set_posx(InSpawnPos.x);
	enemyInfo.set_posy(InSpawnPos.y);
	info.set_speed(InSpeed);
	SetPos(InSpawnPos);
	SetSpeed(InSpeed);
}

void Enemy::Move(float deltaTime)
{
	currPosY = enemyInfo.posy();
	if (info.name() == "HalfEnemy") {
		enemyInfo.set_enemytype(Protocol::ENEMY_TYPE_HALF);
		currPosY += (deltaTime * GetSpeed());
	}
	else if (info.name() == "WhiteEnemy") {
		enemyInfo.set_enemytype(Protocol::ENEMY_TYPE_WHITE);
		currPosY += (deltaTime * GetSpeed());
	}
	enemyInfo.set_posy(currPosY);
	enemyInfo.set_objectid(info.objectid());
	SetPos(Vector(enemyInfo.posx(), enemyInfo.posy()));
}

void Enemy::OnComponentBeginOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other)
{
	Super::OnComponentBeginOverlap(collider, other);
	if (other != nullptr) {
		if (auto missile = dynamic_pointer_cast<SMissile>(other->GetOwner())
			) {
			other->GetOwner()->RemoveComponent(other);
			GET_SINGLE(SCollisionManager)->RemoveCollider(other);
			GRoom->RemoveObject(other->GetOwner()->GetObjectID());
			Damaged();
			if (GetHp() <= 0) {
				shared_ptr<Player> HitPlayer = dynamic_pointer_cast<Player>(missile->GetOwner());
				GET_SINGLE(SCollisionManager)->RemoveCollider(collider);
//				Die(HitPlayer);
				GRoom->RemoveObject(GetObjectID());
			}
		}
	}
}

void Enemy::OnComponentEndOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other)
{
	Super::OnComponentEndOverlap(collider, other);
}
