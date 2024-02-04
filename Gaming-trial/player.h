#pragma once
#include "GameObject.h"
#include "box.h"
#include "sgg/graphics.h"


class Player : public GameObject, public Box
{

	graphics::Brush m_brush_player_debug;
	graphics::Brush m_brush_text;
	graphics::Brush m_brush_player;
	graphics::Brush m_brush_lives[5] = {
		graphics::Brush(), graphics::Brush(),
		graphics::Brush(),graphics::Brush(),graphics::Brush()
	};
	graphics::Brush m_brush_wallet;


	const float m_gravity = 10.f;
	const float m_accel_vertical = 7.0f;
	const float m_accel_horizontal = 140.0f;
	const float m_max_velocity = 5.5f;

	std::vector<std::string> run_animations;
	std::vector<std::string> run_animations_left;
	std::vector<std::string> fight_animations;
	std::vector<std::string> fight_animations_left;
	std::vector<std::string> idle_animations;
	std::vector<std::string> idle_animations_left;
	std::vector<std::string> down_animations;
	std::vector<std::string> life_animations;
	std::vector<std::string> death_animations;

	void movePlayer(float dt);
	void attack(float dt);
	bool attack_pressed = false;
	float m_hit_distanse_from_player;
	int m_wallet = 0;
	float m_damage = 0.0250f;

public:

	Player(std::string name) :GameObject(name) {}
	bool watching_Right = true;
	float m_vx = 0.0f;
	float m_vy = 0.0f;
	float life = 10.0f;

	void update(float dt) override;
	void init() override;
	void draw() override;

	bool getAttack();
	float getHitDistnaseFromPlayer();
	void setHitDistanseFromPlayer(const float& HitDis);

	void addToWallet(int amount);
	int getWallet();

	float getDamage();
	void setDamage(float damage);

	void inscreaseDamage();

	void reduceFromWallet(int amount);
	
protected:

	void drawDebug() override;
	

};
