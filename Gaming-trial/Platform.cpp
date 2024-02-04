#include "Platform.h"
#include "GameState.h"
#include <iostream>
using namespace std;


void Platform::update(float dt)
{
	
	
	
}

void Platform::init()
{
	//brush of Platform(floor)
	m_pos_x = m_state->getCanvasWidth() / 2.0f;// +m_state->m_global_offset_x;
	m_pos_y = m_state->getCanvasHeight();// +m_state->m_global_offset_y;

	m_brush_platform.fill_opacity = 1.0f;
	m_brush_platform.outline_opacity = 0.0f;
	m_brush_platform.texture = m_state->getFullAssetPath("oak_woods_tileset_trial.png");

	m_brush_platform_debug.fill_opacity = 0.1f;
	m_brush_platform_debug.fill_color[0] = 0.2f;
	m_brush_platform_debug.fill_color[1] = 1.0f;
	m_brush_platform_debug.fill_color[2] = 0.1f;
	m_brush_platform_debug.outline_color[0] = 0.3f;
	m_brush_platform_debug.outline_color[1] = 1.0f;
	m_brush_platform_debug.outline_color[2] = 0.1f;
	m_width = m_state->getCanvasWidth() * 5.f;
	m_height = 0.9f;
}

void Platform::draw()
{
	
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;

	//cout << "x,y : " << x << " " << y << endl;
	

	graphics::drawRect(x, y, m_width, m_height, m_brush_platform);

	if(m_state->m_debugging)
		graphics::drawRect(x,y, m_width, m_height, m_brush_platform_debug);
}

