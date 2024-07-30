#include "pch.h"
#include "ExplosionEffect.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"

ExplosionEffect::ExplosionEffect()
{
	flipbookExplosion = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ExplosionEffect");

	SetFlipbook(flipbookExplosion);
	
}

ExplosionEffect::~ExplosionEffect()
{

}

void ExplosionEffect::BeginPlay()
{
	Super::BeginPlay();
}

void ExplosionEffect::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (IsAnimationEnded()) {
		GET_SINGLE(SceneManager)->GetCurrentScene()->RemoveActor(this);
	}
}

void ExplosionEffect::Render(HDC hdc)
{
	Super::Render(hdc);
}
