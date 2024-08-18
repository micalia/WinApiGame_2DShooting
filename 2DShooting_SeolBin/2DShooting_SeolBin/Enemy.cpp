#include "pch.h"
#include "Enemy.h"
#include "Player.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "EnemyMissile.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Scene.h"
#include "ExplosionEffect.h"
#include "Missile.h"

Enemy::Enemy()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"EnemyMissile", L"Sprite\\Projectile\\EnemyBullet.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"EnemyMissile", GET_SINGLE(ResourceManager)->GetTexture(L"EnemyMissile"));
}

Enemy::~Enemy()
{

}

void Enemy::BeginPlay()
{
	Super::BeginPlay();
}

void Enemy::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void Enemy::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Enemy::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	Super::OnComponentBeginOverlap(collider, other);

	if (other != nullptr) {
		if (auto missile = dynamic_cast<Missile*>(other->GetOwner())
			) {
			Damaged();
 			if (hp <= 0) {
				Player* HitPlayer = dynamic_cast<Player*>(missile->GetOwner());
				GET_SINGLE(CollisionManager)->RemoveCollider(collider);
				Die(HitPlayer);
			}
			GET_SINGLE(CollisionManager)->RemoveCollider(other);
			GET_SINGLE(SceneManager)->GetCurrentScene()->RemoveActor(missile);
		}
	}
}

void Enemy::Die(Player* WhoHitMe)
{
	ExplosionEffect* explosionEffect = new ExplosionEffect();
	explosionEffect->SetPos(GetPos());
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(explosionEffect);
	GET_SINGLE(SceneManager)->GetCurrentScene()->RemoveActor(this);
	_dirtyFlag = true;

	Server_AddScore(WhoHitMe, GetKillScore());
}

void Enemy::FindPlayer()
{
	auto& playerArr = GET_SINGLE(SceneManager)->GetCurrentScene()->_actors[LAYER_Player];
	if (playerArr.size() == 2) {
		int ranVal = Utils::RandomIntegerRange(0, 1);
		target = static_cast<Player*>(playerArr[ranVal]);
	}
	else if(playerArr.size() == 1) {
		target = static_cast<Player*>(playerArr[0]);
	}
}

void Enemy::Server_AddScore(Player* whoKillMe, int32 addScore)
{
	if (_dirtyFlag == false && whoKillMe == nullptr)
		return;

	whoKillMe->scoreInfo.set_enemyscore(addScore);
	whoKillMe->scoreInfo.set_playername(whoKillMe->GetName());
	SendBufferRef sendBuffer = ClientPacketHandler::Make_C_ScoreCalculate(whoKillMe);
	GET_SINGLE(NetworkManager)->SendPacket(sendBuffer);
}

