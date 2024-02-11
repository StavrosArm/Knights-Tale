#include "player.h"
#include <sgg/graphics.h>
#include "GameState.h"
#include <iostream>
#include <iomanip>



void Player::movePlayer(float dt)
{	
	float prev_pos_y = 0.0;
	std::string path = m_state->getAssetDir();
	float delta_time = dt / 1000.0f;

	float move = 0.0f;

	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		move -= 0.1f;
		watching_Right = false;

	}
	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		move += 0.1f;
		watching_Right = true;
		
	}
	if (m_vx) {
		if (watching_Right) {
			int s = (int)fmodf(fabs(1000.f - m_pos_x), run_animations.size());
			m_brush_player.texture = run_animations[s];
		}
		else if (!watching_Right)
		{
			int s = (int)fmodf(fabs(1000.f - m_pos_x), run_animations.size());
			m_brush_player.texture = run_animations_left[s];
		}
	}
	else m_brush_player.texture = watching_Right ? idle_animations[0] : idle_animations_left[0];

	

	

	m_vx = std::min(m_max_velocity,m_vx + delta_time * move * m_accel_horizontal);
	m_vx = std::max(-m_max_velocity, m_vx);

	m_vx -= 0.18f * m_vx/(0.1f+fabs(m_vx));
	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;
	m_pos_x += delta_time * m_vx;

	if (m_vy == 0.0f)
		m_vy -= graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f;
	
	m_vy += delta_time * m_gravity;

	prev_pos_y = m_pos_y;
	m_pos_y += m_vy * delta_time;
	if (m_pos_y <= prev_pos_y){
		
		m_brush_player.texture = down_animations[4];
	}
	else if(fabs(m_pos_y-prev_pos_y)>0.02f)
	{
		
		m_brush_player.texture = down_animations[7];
	}
	

}

void Player::attack(float dt)
{
	float delta_time = dt / 1000.0f;
	if (watching_Right) {
		int s = (int)fmodf(graphics::getGlobalTime() / 100.f, fight_animations.size());
		m_brush_player.texture = fight_animations[s];
	}
	else 
	{
		int s = (int)fmodf(graphics::getGlobalTime() / 100.f, fight_animations_left .size());
		m_brush_player.texture = fight_animations_left[s];
	}

	
}


void Player::update(float dt)
{
	

	if (isActive() && life <=0) 
	{
		int s = (int)fmodf(graphics::getGlobalTime()/120.f, death_animations.size());
		m_brush_player.texture = death_animations[s];
		if (s == death_animations.size() - 1)
		{
			setActive(false);
		}
	}
	else
	{
		movePlayer(dt);
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			attack(dt);
			attack_pressed = true;
		}
		else {
			attack_pressed = false;
		}

		m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
		m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	}

	

	GameObject::update(dt);
}

void Player::init()
{
	std::string path = m_state->getAssetDir() + "/player";
	run_animations = graphics::preloadBitmaps(path+"/run");
	fight_animations = graphics::preloadBitmaps(path + "/attack");
	idle_animations = graphics::preloadBitmaps(path + "/idle");
	idle_animations_left = graphics::preloadBitmaps(path + "/idle_left");
	run_animations_left= graphics::preloadBitmaps(path + "/run_left");
	down_animations = graphics::preloadBitmaps(path + "/down");
	fight_animations_left= graphics::preloadBitmaps(path + "/attack_left");
	life_animations = graphics::preloadBitmaps(path + "/life");
	death_animations = graphics::preloadBitmaps(path + "/death");

	//position tou player wste na amfanizetai katw aristera kata thn enarksh tou paixnidiou
	m_pos_x = -30.f;
	m_pos_y = m_state->getCanvasHeight()-1.f;
	//Xrhsimopoioume to akoloutho height sto debug mode
	m_height = 1.3f;
	m_width = 1.f;

	//Apostasth tou kedrou tou kamva apo ton player
	m_state->m_global_offset_x = m_state->getCanvasWidth()/2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight()/2.0f - m_pos_y;


	
	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = idle_animations[0];

	m_brush_player_debug.fill_opacity = 0.1f;
	m_brush_player_debug.outline_opacity = 0.1f;
	m_brush_player_debug.fill_color[0] = 1.0f;
	m_brush_player_debug.fill_color[1] = 0.2f;
	m_brush_player_debug.fill_color[2] = 0.2f;
	m_brush_player_debug.outline_color[0] = 1.0f;
	m_brush_player_debug.outline_color[1] = 0.3f;
	m_brush_player_debug.outline_color[2] = 0.3f;

	m_brush_text.fill_color[0] = 1.0f;
	m_brush_text.fill_color[1] = 0.0f;
	m_brush_text.fill_color[2] = 0.0f;

	for (int i = 0; i < 5; i++) {
		m_brush_lives[i].texture = life_animations[0];
		m_brush_lives[i].outline_opacity = 0.0f;
	}

	m_brush_wallet.fill_color[0] = 2.120f;
	m_brush_wallet.fill_color[1] = 1.75f;
	m_brush_wallet.fill_color[2] = 0.55f;





	
}

void Player::draw()
{
	
	//Kanoyme draw ton player kathe fora sto idio shmeio kai apla kounietai to background
	graphics::drawRect(m_state->getCanvasWidth()/2.0f , m_state->getCanvasHeight()/2.0f, 3.f-1.5f, 3.f, m_brush_player);
	if (m_state->m_debugging) {
		drawDebug();
	}	

	
	graphics::drawText(m_state->getCanvasWidth()-2.f,0.8f, 0.8f, std::to_string(m_wallet) + "$", m_brush_wallet);
	//Edw gemizoume tis kardies tou paikti.Kathe kardia exei 3 frames
	//Gemati , misi kai adeia. Ama i zoi tou paikti pesei kata 2 float (sunolika einai 10)
	//Xanei mia zoi olokliri. Opote metrate anapoda tis kardies kai allazoume ta frames analogws.
	for (int i = 4; i >-1; i--) {
		if (life <= 0.0f) {
			m_brush_lives[i].texture = life_animations[2];
		}
		else {
			if ((life >= 2 * i + 1) && (life < 2 * i + 2)) {
				m_brush_lives[i].texture = life_animations[1];
			}
			else if ((life >= 2 * i) && (life < 2 * i + 1)) {
				m_brush_lives[i].texture = life_animations[2];
			}
			else if (life >= 2 * i + 2) {
				m_brush_lives[i].texture = life_animations[0];
			}

		}
		graphics::drawRect(1.0f+0.6f*i, 0.5f, 0.5f, 0.5f, m_brush_lives[i]);
	}
}

bool Player::getAttack()
{
	return attack_pressed;
}

float Player::getHitDistnaseFromPlayer()
{
	return m_hit_distanse_from_player;
}

void Player::setHitDistanseFromPlayer(const float& HitDis)
{
	m_hit_distanse_from_player = HitDis;
}

void Player::addToWallet(int amount)
{
	m_wallet += amount;
}

int Player::getWallet() {

	return m_wallet;
}

float Player::getDamage()
{
	return m_damage;
}

void Player::setDamage(float damage)
{
	m_damage = damage;
}

void Player::reduceFromWallet(int amount)
{
	m_wallet -= amount;
}


void Player::inscreaseDamage()
{
	m_damage += 0.010;
}


void Player::drawDebug() {

	// emfanizoume to debug mode toy stis idies suntetagmenes kathe fora kathws o paixths einai statheros
	graphics::drawRect(m_state->getCanvasWidth() / 2.0f, m_state->getCanvasHeight() / 2.0f,
		m_width, m_height, m_brush_player_debug);
	//emfanizoyme me keimeno tis suntetagmenes tou pou brisketai ston kamva auth thn stigmh o player
	graphics::drawText(m_state->getCanvasWidth() / 2.0f -2.5f, m_state->getCanvasHeight()/2.0f - 1.0f, 0.6f,
		"(" +std::to_string(m_pos_x) + "," + std::to_string(m_pos_y) + ")", m_brush_text);

}
