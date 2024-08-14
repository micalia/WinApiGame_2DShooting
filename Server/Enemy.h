#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
	using Super = GameObject;
public:
	Enemy();
	virtual ~Enemy();

	virtual void Update();


};

