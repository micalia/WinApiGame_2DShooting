#pragma once

enum class SceneType
{
	None,
	DevScene,
	GameScene,
	EditScene
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_EnemyMissile,
	LAYER_Enemy,
	LAYER_BULLET,
	LAYER_Player,
	LAYER_OBJECT,
	LAYER_WALL,
	// ...
	LAYER_UI,

	LAYER_MAXCOUNT
};

enum COLLISION_LAYER_TYPE : uint8
{
	CLT_NO_COLLISION,
	CLT_OBJECT,
	CLT_PLAYER,
	CLT_MISSILE,
	CLT_ENEMY,
	CLT_ENEMY_MISSILE,
	CLT_GROUND,
	CLT_WALL,
	// ...
};

enum class ColliderType
{
	Box,
	Sphere,
};

enum Dir 
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
};