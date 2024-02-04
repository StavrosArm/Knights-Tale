#include "FireTrap.h"

void FireTrap::checkcollision()
{

}

void FireTrap::update(float dt)
{
	checkcollision();
}

void FireTrap::drawDebug()
{
}

void FireTrap::init()
{
	staticObj::init();
	m_staticObj_br.texture = m_state->getFullAssetPath("long_wood_spike_05.png");
}

void FireTrap::draw()
{
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;

	graphics::drawRect(x, y, 0.5f , m_staticObj_size, m_staticObj_br);
	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_width, m_height, m_staticObj_br_debug);
}

FireTrap::FireTrap(float x, float y, float width, float height, float staticObjSize):staticObj(x,y,width,height,staticObjSize)
{
}
