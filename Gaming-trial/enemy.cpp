#include "enemy.h"
#include "GameState.h"
#include <iostream>

void Enemy::update(float dt)
{
	
	if ((fabs(m_pos_x - m_state->getPlayer()->m_pos_x) <= m_state->getPlayer()->getHitDistnaseFromPlayer()) && (m_state->getPlayer()->getAttack()))
	{
		m_life -= m_state->getPlayer()->getDamage();
	}
	if (m_life <= 0.f)
		setActive(false);
	
}

void Enemy::followPlayer() 
{	
	
	if (m_state->getPlayer()->m_pos_x - m_pos_x < 0) {
		int s = (int)fmodf(1000.f - 8.f * m_pos_x, m_run_animations_left.size());
		m_brush_enemy.texture = m_run_animations_left[s];
	}
	else if (m_state->getPlayer()->m_pos_x - m_pos_x > 0) {
		int s = (int)fmodf(1000.f - 8.f * m_pos_x, m_run_animations.size());
		m_brush_enemy.texture = m_run_animations[s];
	}
	
}

void Enemy::init()
{
	m_attack_animations = graphics::preloadBitmaps(m_state->getAssetDir()+m_path+"attack");
	m_attack_animations_left = graphics::preloadBitmaps(m_state->getAssetDir() + m_path+"attack_left");
	m_run_animations= graphics::preloadBitmaps(m_state->getAssetDir() + m_path+"run");
	m_run_animations_left = graphics::preloadBitmaps(m_state->getAssetDir() + m_path+"run_left");

	m_brush_enemy.fill_opacity = 1.0f;
	m_brush_enemy.outline_opacity = 0.0f;
	m_brush_enemy.texture = m_attack_animations[0];


	m_brush_enemy_debug.fill_opacity = 0.1f;
	m_brush_enemy_debug.outline_opacity = 0.1f;
	m_brush_enemy_debug.fill_color[0] = 1.0f;
	m_brush_enemy_debug.fill_color[1] = 0.2f;
	m_brush_enemy_debug.fill_color[2] = 0.2f;
	m_brush_enemy_debug.outline_color[0] = 1.0f;
	m_brush_enemy_debug.outline_color[1] = 0.3f;
	m_brush_enemy_debug.outline_color[2] = 0.3f;

}

Enemy::Enemy(float x, float y, float width, float height, std::string path, float hit_distanse ,float life):Box(x,y,width,height) 
{
	m_life = life;
	m_path = path;
	m_hit_distanse = hit_distanse;

}


void Enemy::draw() 
{
	float x = m_state->m_global_offset_x+ m_pos_x;
	float y = m_state->m_global_offset_y+ m_pos_y ;

	graphics::drawRect(x, y, 3.f, 3.f, m_brush_enemy);

	if (m_state->m_debugging)
		graphics::drawRect(x,y, m_width, m_height, m_brush_enemy_debug);

}