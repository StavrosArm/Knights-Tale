#pragma once
#pragma once
#include "Box.h"
#include "GameState.h"
#include "GameObject.h"
#include "enemy.h"

class DeathBringer : public Enemy
{
	std::vector<std::string> m_death_animations;

public:
	const float m_damage = 0.025f;

	void update(float dt) override;
	void init() override;
	void draw() override;
	DeathBringer(float x, float y, float width, float height, std::string path, float hit_distanse, float life);
};