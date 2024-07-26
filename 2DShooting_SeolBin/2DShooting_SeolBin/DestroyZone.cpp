#include "pch.h"
#include "DestroyZone.h"
#include "SceneManager.h"
#include "Collider.h"
#include "Scene.h"
#include "Missile.h"

DestroyZone::DestroyZone()
{

}

DestroyZone::~DestroyZone()
{

}

void DestroyZone::BeginPlay()
{
	Super::BeginPlay();
}

void DestroyZone::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void DestroyZone::Render(HDC hdc)
{
	Super::Render(hdc);
}

void DestroyZone::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	Super::OnComponentBeginOverlap(collider, other);
	
	if (other != nullptr) {
		if (dynamic_cast<Missile*>(other->GetOwner())) {
			GET_SINGLE(SceneManager)->GetCurrentScene()->RemoveActor(other->GetOwner());
		}
	}
}
