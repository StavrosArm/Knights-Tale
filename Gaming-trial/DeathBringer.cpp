#include "DeathBringer.h"

void DeathBringer::update(float dt)
{
	float delta_time = dt / 1000.f;

	if ((m_life <= 0.f) && (isActive())) {
		int s = (int)fmodf(graphics::getGlobalTime() / 100.f, m_death_animations.size());
		m_brush_enemy.texture = m_death_animations[s];
		if (s == m_death_animations.size() - 1)
		{
			setActive(false);
		}
	}
	else if ((m_life > 0.f) && (isActive()))
	{
		if ((fabs(m_pos_x - m_state->getPlayer()->m_pos_x) <= m_hit_distanse) && (fabs(m_pos_y - m_state->getPlayer()->m_pos_y) <= 0.5f)) {
			if (m_state->getPlayer()->m_pos_x - m_pos_x < 0) {


				m_state->getPlayer()->setHitDistanseFromPlayer(0.95);

				if ((m_state->getPlayer()->watching_Right)) {
					if ((fabs(m_pos_x - m_state->getPlayer()->m_pos_x) <= m_state->getPlayer()->getHitDistnaseFromPlayer()) && (m_state->getPlayer()->getAttack()))
					{
						m_life -= m_state->getPlayer()->getDamage();
					}
				}
				int s = (int)fmodf(graphics::getGlobalTime() / 100.f, m_attack_animations_left.size());
				m_brush_enemy.texture = m_attack_animations_left[s];
				m_state->getPlayer()->life -= m_damage;

			}
			else  if (m_state->getPlayer()->m_pos_x - m_pos_x >= 0) {

				m_state->getPlayer()->setHitDistanseFromPlayer(0.95);

				if ((!m_state->getPlayer()->watching_Right)) {
					if ((fabs(m_pos_x - m_state->getPlayer()->m_pos_x) <= m_state->getPlayer()->getHitDistnaseFromPlayer()) && (m_state->getPlayer()->getAttack()))
					{
						m_life -= m_state->getPlayer()->getDamage();
					}
				}
				int s = (int)fmodf(graphics::getGlobalTime() / 100.f, m_attack_animations.size());
				m_brush_enemy.texture = m_attack_animations[s];
				m_state->getPlayer()->life -= m_damage;
			}
		}
	}
	m_vy = delta_time * delta_time * m_gravity;
	m_pos_y += m_vy;
}

void DeathBringer::init()
{
	Enemy::init();
	m_death_animations = graphics::preloadBitmaps(m_state->getAssetDir() + m_path + "death");
}

void DeathBringer::draw()
{
	Enemy::draw();
}

DeathBringer::DeathBringer(float x, float y, float width, float height, std::string path, float hit_distanse, float life) :Enemy(x, y, width, height, path, hit_distanse, life)
{
}
