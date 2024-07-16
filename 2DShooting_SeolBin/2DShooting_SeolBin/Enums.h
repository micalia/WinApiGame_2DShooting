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
	LAYER_OBJECT,
	// ...
	LAYER_UI,

	LAYER_MAXCOUNT
};

enum COLLISION_LAYER_TYPE : uint8
{
	CLT_OBJECT,
	CLT_GROUND,
	CLT_WALL,
	// ...
};

enum class ColliderType
{
	Box,
	Sphere,
};