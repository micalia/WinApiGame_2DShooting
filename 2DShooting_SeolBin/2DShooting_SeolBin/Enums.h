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
	LAYER_Player,
	LAYER_BULLET,
	LAYER_OBJECT,
	LAYER_WALL,
	// ...
	LAYER_UI,

	LAYER_MAXCOUNT
};

enum COLLISION_LAYER_TYPE : uint8
{
	CLT_OBJECT,
	CLT_PLAYER,
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