#include "coin.h"

void Coin::update(float dt)
{
	int s = (int)fmodf(graphics::getGlobalTime() / 100.f, m_coin_animations.size());
	m_coin_brush.texture = m_coin_animations[s];
}

void Coin::init()
{
	m_coin_animations = graphics::preloadBitmaps(path);
	m_coin_brush.fill_opacity = 1.0f;
	m_coin_brush.outline_opacity = 0.0f;

	m_coin_brush.texture = m_coin_animations[0];

}

void Coin::draw() 
{
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;

	graphics::drawRect(x, y, m_width, m_height, m_coin_brush);


}

Coin::Coin(float x, float y, float width, float height) : Box(x, y, width, height) {}

int Coin::getValue()
{
	return m_value;
}


