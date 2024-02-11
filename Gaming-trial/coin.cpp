#include "coin.h"


/*Coins are positioned in specific places , and they change their animations based on the time 
that has passed.*/
void Coin::update(float dt)
{
	int s = (int)fmodf(graphics::getGlobalTime() / 100.f, m_coin_animations.size());
	m_coin_brush.texture = m_coin_animations[s];
}

/*We load the bitmaps and set the texture as the first animation.*/
void Coin::init()
{
	m_coin_animations = graphics::preloadBitmaps(path);
	m_coin_brush.fill_opacity = 1.0f;
	m_coin_brush.outline_opacity = 0.0f;

	m_coin_brush.texture = m_coin_animations[0];

}

/*We draw the coin based on the global offest.*/
void Coin::draw() 
{
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;

	graphics::drawRect(x, y, m_width, m_height, m_coin_brush);


}
/*A coin is a box that intersects with the player.*/
Coin::Coin(float x, float y, float width, float height) : Box(x, y, width, height) {}


int Coin::getValue()
{
	return m_value;
}


