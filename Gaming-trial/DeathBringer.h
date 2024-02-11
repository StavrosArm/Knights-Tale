#pragma once
#pragma once
#include "Box.h"
#include "GameState.h"
#include "GameObject.h"
#include "enemy.h"

/*Ο Deathbringer είναι το τελευταίο boss και κληρονομέι το enemy και απλά του έχουμε προσθέσει και ένα vector με τα deaths sprites.
 Επιπλέον το damage του είναι ανεβασμένο σε σχέση με τους άλλους εχθρους.
*/
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