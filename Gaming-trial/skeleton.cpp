#include "skeleton.h"

void Skeleton::update(float dt)
{
	//std::cout <<"Line 7 at enemyy.cpp : "<< fabs(m_pos_y - m_state->getPlayer()->m_pos_y) << std::endl;
	float delta_time = dt / 1000.f;
	
//To if pou akolouthei elegxei an h apoluth apostasth tou exthrou apo ton paixth einai mikroterh tou 1.40(m_hit_distanse).
//Epipleon elegxei an h apoluth apostash upsous apo ton paixth einai mikroterh apo 0.5
	if ((fabs(m_pos_x - m_state->getPlayer()->m_pos_x) <= m_hit_distanse) && (fabs(m_pos_y - m_state->getPlayer()->m_pos_y) <= 0.5f)) {
		if (m_state->getPlayer()->m_pos_x - m_pos_x < 0) {

			//To if pou akoloythei elegxei ti eidous enemy antimetwpizei o paixts kai analogws thetei thn 
			//thn apostash tou hit tou paixth pou tha kanei damage ston antistoixo enemy
			m_state->getPlayer()->setHitDistanseFromPlayer(0.95);

			if ((m_state->getPlayer()->watching_Right)) Enemy::update(dt);
			//To if pou akoloythei elegxei an h apostash tou paixth apo ton enemy einai mikroterh tou 0.95.
			//Epipleon elegxei an o paixts epitithetai koitwntas deksia.Auto to kanoume gia na apofugoume 
			//thn periptwsh na einai o paixtis me plath kai na kanei damage ston exthro.
			int s = (int)fmodf(graphics::getGlobalTime() / 100.f, m_attack_animations_left.size());
			m_brush_enemy.texture = m_attack_animations_left[s];
			m_state->getPlayer()->life -= m_damage;
		}
		else  if (m_state->getPlayer()->m_pos_x - m_pos_x >=0) {

			m_state->getPlayer()->setHitDistanseFromPlayer(0.95);

			if ((!m_state->getPlayer()->watching_Right)) Enemy::update(dt);

			int s = (int)fmodf(graphics::getGlobalTime() / 100.f, m_attack_animations.size());
			m_brush_enemy.texture = m_attack_animations[s];
			m_state->getPlayer()->life -= m_damage;
		}
	}	
	m_vy = delta_time * delta_time * m_gravity;
	m_pos_y += m_vy;
}

void Skeleton::init() {
	Enemy::init();
}

void Skeleton::draw() {
	Enemy::draw();

}

Skeleton::Skeleton(float x, float y, float width, float height, std::string path, float hit_distanse,float life):Enemy(x,y,width,height,path,hit_distanse,life)
{
	
}

