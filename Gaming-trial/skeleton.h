#pragma once
#include "Box.h"
#include "GameState.h"
#include "GameObject.h"
#include "enemy.h"

class Skeleton : public Enemy
{


public:
	const float m_damage = 0.0175f;

	void update(float dt) override;
	void init() override;
	void draw() override;
	Skeleton(float x, float y, float width, float height, std::string path, float hit_distanse,float life);
};