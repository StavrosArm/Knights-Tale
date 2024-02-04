#include "staticObj.h"
#include "GameState.h"

void staticObj::update(float dt)
{
}

void staticObj::drawDebug()
{
}

void staticObj::init()
{
	m_staticObj_br.fill_opacity = 1.0f;
	m_staticObj_br.outline_opacity = 0.0f;

	m_staticObj_br_debug.fill_opacity = 0.1f;
	m_staticObj_br_debug.fill_color[0] = 0.2f;
	m_staticObj_br_debug.fill_color[1] = 1.0f;
	m_staticObj_br_debug.fill_color[2] = 0.1f;
	m_staticObj_br_debug.outline_color[0] = 0.3f;
	m_staticObj_br_debug.outline_color[1] = 1.0f;
	m_staticObj_br_debug.outline_color[2] = 0.1f;
}

void staticObj::draw()
{
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;

	graphics::drawRect(x, y, m_width + 0.5f * m_width, m_staticObj_size,m_staticObj_br);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_width, m_height, m_staticObj_br_debug);
}

staticObj::staticObj(float x, float y, float width, float height,float staticObjSize):Box(x,y,width,height)
{
	m_staticObj_size = staticObjSize;
}
