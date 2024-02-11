#include "Archer.h"
#include <iostream>


/*The update function is responsible for changing the animations of the archer based on the position of the player.
An archer can shoot at a straight line , looking up or looking down.The animations change based on the players 
position.*/

/*If the player is at a range that he can damage the archer we call the archer's ancestor(enemy) update
to handle the life damage of the archer.
In additions we update the archer arrows , and we check if any arrows are inactive in order to destroy them.*/
void Archer::update(float dt)
{
	float delta_time = dt / 1000.f;
	if (fabs(m_pos_x - m_state->getPlayer()->m_pos_x < 12.0f) && m_pos_x - m_state->getPlayer()->m_pos_x > 0) {

		if (m_pos_y - m_state->getPlayer()->m_pos_y <= -1.0)
		{
			int s = (int)fmodf(graphics::getGlobalTime() / 200.f, m_low_attack_left_animations.size());
			m_brush_enemy.texture = m_low_attack_left_animations[s];
		}
		else if ((m_pos_y - m_state->getPlayer()->m_pos_y > -1.0) && (m_pos_y - m_state->getPlayer()->m_pos_y < 0.0))
		{
			if (m_state->getPlayer()->watching_Right)
			{
				m_state->getPlayer()->setHitDistanseFromPlayer(0.95);
				Enemy::update(dt);
			}
			int s = (int)fmodf(graphics::getGlobalTime() / 200.f, m_attack_animations_left.size());
			m_brush_enemy.texture = m_attack_animations_left[s];
		}
		else if (m_pos_y - m_state->getPlayer()->m_pos_y >= 0.0 && m_pos_y - m_state->getPlayer()->m_pos_y <=4)
		{
			int s = (int)fmodf(graphics::getGlobalTime() / 200.f, m_high_attack_left_animations.size());
			m_brush_enemy.texture = m_high_attack_left_animations[s];
		}
	}
	else if (fabs(m_pos_x - m_state->getPlayer()->m_pos_x < 12.0f) && m_pos_x - m_state->getPlayer()->m_pos_x < 0)
	{
		if (m_pos_y - m_state->getPlayer()->m_pos_y <= -1.0)
		{
			int s = (int)fmodf(graphics::getGlobalTime() / 200.f, m_low_attack_animations.size());
			m_brush_enemy.texture = m_low_attack_animations[s];
		}
		else if ((m_pos_y - m_state->getPlayer()->m_pos_y > -1.0) && (m_pos_y - m_state->getPlayer()->m_pos_y < 0.0))
		{
			if (!m_state->getPlayer()->watching_Right)
			{
				m_state->getPlayer()->setHitDistanseFromPlayer(0.95);
				Enemy::update(dt);
			}
			int s = (int)fmodf(graphics::getGlobalTime() / 200.f, m_attack_animations.size());
			m_brush_enemy.texture = m_attack_animations[s];
		}
		else if (m_pos_y - m_state->getPlayer()->m_pos_y >= 0.0 && m_pos_y - m_state->getPlayer()->m_pos_y <= 4)
		{
			int s = (int)fmodf(graphics::getGlobalTime() / 200.f, m_high_attack_animations.size());
			m_brush_enemy.texture = m_high_attack_animations[s];
		}
	}


	for (auto& ar : m_arrows) {
		if (ar->isActive()) {
			ar->update(dt);
		}
		
	}
	GarbageCollection();
	m_vy = delta_time * delta_time * m_gravity;
	m_pos_y += m_vy;
}


/*Loading the animations for the archer and calling it's ancestor init() for the common characteristics.*/
void Archer::init() {

	m_high_attack_animations=graphics::preloadBitmaps(m_state->getFullAssetPath(m_path+"high_attack"));
	m_high_attack_left_animations = graphics::preloadBitmaps(m_state->getFullAssetPath(m_path + "high_attack_left"));
	m_low_attack_animations =graphics::preloadBitmaps(m_state->getFullAssetPath(m_path + "low_attack"));
	m_low_attack_left_animations = graphics::preloadBitmaps(m_state->getFullAssetPath(m_path + "low_attack_left"));
	Enemy::init();
}


/*The archer thows arrows with a certain frequency. If conditions are met , a new arrow is created, 
which takes as arguments the position of the archer (minus something for visual reasons) and the archer himself.*/
void Archer::draw() 
{	
	Enemy::draw();

	if (!fmod(count, 100)) {
		
		if (fabs(m_state->getPlayer()->m_pos_y - m_pos_y) <= 8.f) {
			if (m_state->getPlayer()->m_pos_x - m_pos_x < 0) {
				Arrow* arrow = new Arrow(m_pos_x - 0.8f, m_pos_y - .2f, 0.25f, 1.f, this);
				arrow->init();

				
				m_arrows.push_back(arrow);
			}
			else
			{
				Arrow* arrow = new Arrow(m_pos_x + 0.8f, m_pos_y - .2f, 0.25f, 1.f, this);
				arrow->init();
				m_arrows.push_back(arrow);
			}
		}
	}

	for (auto& ar : m_arrows) {
		if (ar->isActive()) {
			ar->draw();
		}
		
	}
	count++;
	
	
}

//Constructor of the archer , calls its ancestor.
Archer::Archer(float x, float y, float width, float height, std::string path, float hit_distanse ,float life) :Enemy(x, y, width, height, path, hit_distanse,life)
{

}

/*The destructor of an archer is reasponsible for deleting all the dynamically created objects remaining after his death.*/
Archer::~Archer()
{
	auto it = m_arrows.begin();
	while (it != m_arrows.end()) {
		if ((*it)->isActive()) {
			delete* it;
			it = m_arrows.erase(it);
		}
		else {
			++it;
		}
	}
}


/*We call the garbage collector in order to erase the inactive arrows*/
void Archer::GarbageCollection()
{
	auto it = m_arrows.begin();
	while (it != m_arrows.end()) {
		if (!(*it)->isActive()) {
			delete* it;
			it = m_arrows.erase(it);
		}
		else {
			++it;
		}
	}
}

//Mia methodos pou epistrefei sthn klash arrow thn faretra tou toksoth me ta arrows
const std::list<Arrow*>& Archer::getArrows() const
{
	return m_arrows;
}