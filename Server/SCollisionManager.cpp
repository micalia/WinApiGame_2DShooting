#include "pch.h"
#include "SCollisionManager.h"
#include "SCollider.h"
#include "Actor.h"
#include "SEnemyMissile.h"
#include "WhiteEnemy.h"
#include "SDestroyZone.h"

void SCollisionManager::Init()
{

}

void SCollisionManager::Update()
{
	vector<shared_ptr<SCollider>>& colliders = _colliders;
	for (int32 i = 0; i < colliders.size(); i++)
	{
		for (int32 j = i + 1; j < colliders.size(); j++)
		{
			shared_ptr<SCollider> src = colliders[i];
			shared_ptr<SCollider> dest = colliders[j];
			if (dest->GetCollisionFlag() == 0)continue; // NoCollision이면 return
			auto srcOwner = src->GetOwner();
			auto destOwner = dest->GetOwner();
			if (srcOwner == nullptr || destOwner == nullptr) continue;
			//콜리젼이 켜져있는가?
			if (src->CheckCollision(dest))
			{
				if (src->_collisionMap.contains(dest) == false)
				{
					src->GetOwner()->OnComponentBeginOverlap(src, dest);
					dest->GetOwner()->OnComponentBeginOverlap(dest, src);
					src->_collisionMap.insert(dest);
					dest->_collisionMap.insert(src);
				}
			}
			else
			{
				if (src->_collisionMap.contains(dest))
				{
					src->GetOwner()->OnComponentEndOverlap(src, dest);
					dest->GetOwner()->OnComponentEndOverlap(dest, src);
					src->_collisionMap.erase(dest);
					dest->_collisionMap.erase(src);
				}
			}
		}
	}

}

void SCollisionManager::AddCollider(shared_ptr<SCollider> collider)
{
	_colliders.push_back(collider);
}

void SCollisionManager::RemoveCollider(shared_ptr<SCollider> collider)
{
	auto it = std::remove(_colliders.begin(), _colliders.end(), collider);
	_colliders.erase(it, _colliders.end());
}
