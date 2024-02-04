#pragma once
#include "GameObject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "player.h"
#include "GameState.h"

class Enemy : public GameObject, public Box 
{
	

public :
	float m_vy = 0.0;
	
	void update(float dt) override;
	void draw() override;
	void init() override;
	void followPlayer();
	Enemy(float x, float y , float width,float height,std::string path,float hit_distanse , float life );
protected:
	float m_life;
	float m_hit_distanse;
	float m_gravity = 5.f;
	

	std::string m_type_of_enemy;
	graphics::Brush m_brush_enemy;
	graphics::Brush m_brush_enemy_debug;

	
	std::vector<std::string> m_run_animations;
	std::vector<std::string> m_run_animations_left;
	std::vector<std::string> m_attack_animations;
	std::vector<std::string> m_attack_animations_left;
	std::string m_path;
};