#pragma once
#include "arrow.h"
#include "enemy.h"
#include <list>


class Archer : public Enemy
{
	std::list <Arrow*> m_arrows;
	std::vector<Arrow*> arrowsToDelete;

	std::vector<std::string>m_high_attack_animations;
	std::vector<std::string>m_high_attack_left_animations;
	std::vector<std::string>m_low_attack_animations;
	std::vector<std::string>m_low_attack_left_animations;

	int count = 0;
	void GarbageCollection();
	

public:
	
	const std::list<Arrow*>& getArrows() const;
	float m_damage = 0.25;
	void init() override;
	void update(float dt) override;
	void draw() override;
	Archer(float x, float y, float width, float height, std::string path, float hit_distanse,float life);
	~Archer();
};

