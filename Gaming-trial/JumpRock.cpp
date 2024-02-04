#include "JumpRock.h"
#include "GameState.h"
#include "player.h"
#include "cmath"

void JumpRock::update(float dt)
{
	float delta_time = dt/1000.f;
	if (first_draw != 0) {
		if (m_move_hor) {
			//std::cout << "THE TIME THAT START" << graphics::getGlobalTime() << " " << time_of_draw << std::endl;
			freq_move = 2.f * sinf(((graphics::getGlobalTime() - time_of_draw) / 2000.f))*delta_time;
			m_pos_x -= freq_move;
		}
		else if (m_move_ver) {
			freq_move = 2.f * sinf(((graphics::getGlobalTime() - time_of_draw) / 700.f))*delta_time;
			m_pos_y += freq_move;
		}
	}
	else {
		time_of_draw = graphics::getGlobalTime();
	}
	first_draw++;
}

void JumpRock::drawDebug()
{
}


void JumpRock::init()
{

	m_jumprock_br.fill_opacity = 1.0f;
	m_jumprock_br.outline_opacity = 0.0f;
	m_jumprock_br.texture = m_state->DecorationsPaths[6];

	m_jumprock_br_debug.fill_opacity = 0.1f;
	m_jumprock_br_debug.fill_color[0] = 0.2f;
	m_jumprock_br_debug.fill_color[1] = 1.0f; 
	m_jumprock_br_debug.fill_color[2] = 0.1f;
	m_jumprock_br_debug.outline_color[0] = 0.3f;
	m_jumprock_br_debug.outline_color[1] = 1.0f;
	m_jumprock_br_debug.outline_color[2] = 0.1f;
	

}

void JumpRock::draw()
{
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;

	//cout << "x,y : " << x << " " << y << endl;

	graphics::drawRect(x, y, m_width+0.5f*m_width, JumpRocksize, m_jumprock_br);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_width, m_height, m_jumprock_br_debug);
}

JumpRock::JumpRock(float x, float y, float width, float height,bool move_horizontically,bool move_vertically) :Box(x, y, width, height)
{
	m_move_hor = move_horizontically;
	m_move_ver = move_vertically;
}


