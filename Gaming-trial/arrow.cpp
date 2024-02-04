#include "arrow.h"
#include "Archer.h"
#include <iostream>
#include "player.h"
#include <numbers>
#include <cmath>
#include <chrono>


/*Updating the arrow's position based on the angle calculated at the cration time (see below).In order for the arrow
to take this path we need to add to the position in the x axis, with the cosine multiplied by a certain 
step, and the position in the y axis with the sine multiplied by a certain step 
(multiplied by delta time of course)*/
void Arrow::update(float dt)
{
	float delta_time = dt / 1000.f;
	if (flag_x)
	{
		m_brush_arrow.texture = m_path_left;
		m_pos_x -= 10.f*std::cos(m_angle)*delta_time;
		if (flag_y) {
			m_pos_y -=  7.f*std::sin(m_angle)* delta_time;
		}
		else {
			m_pos_y += 10.f*std::sin(m_angle)* delta_time;
		}


	}
	else if(!flag_x)
	{
		m_brush_arrow.texture = m_path;
		m_pos_x += 10.f*std::cos(m_angle)*delta_time;
		if (flag_y) {
			m_pos_y -= 7.f*std::sin(m_angle)*delta_time;
		}
		else {
			m_pos_y += 10.f*std::sin(m_angle)*delta_time;
		}

	}

	//If the arrow goes further than a 12 float radius we deactivate
	// We don't want an arrow to flying from the other end to damage the player.
	if((fabs(m_pos_x - m_archer->m_pos_x)>12.f)||(fabs(m_pos_y - m_archer->m_pos_y) > 12.f))
	{
		this->m_active = false;
	}

	//If the arrow intersected with the player we take some life out of the player , 
	//and deactivate the arrow.
	if (m_state->getPlayer()->intersect(*this)) {
		this->m_active = false;
		m_state->getPlayer()->life -= m_archer->m_damage;
	}
}


//Every arrow has angle that aims for the player. Based on the position of y , that angle would either be the 
//angle its self or 360 degrees plus that angle.
void Arrow::draw()
{
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;

	if (flag_x) {
		if (!flag_y) {
			graphics::setOrientation(static_cast<float>(360.f + m_angle * 180.0 / 3.14f));
		}
		else {
			graphics::setOrientation(-static_cast<float>(m_angle * 180.0 / 3.14f));
		}
	}
	else {
		if (!flag_y) {
			graphics::setOrientation(-static_cast<float>(360.f + m_angle * 180.0 / 3.14f));
		}
		else {
			graphics::setOrientation(static_cast<float>(360.f + m_angle * 180.0 / 3.14f));
		}
		
	}
		
		graphics::drawRect(x, y, m_width+1.85f, m_height, m_brush_arrow);
		graphics::resetPose();
}

/*Based on the player's position when the arrow is created , we need to calculate the angle that the arrow needs to 
follow in order to aim for the player.The simplest way to do that was by calculating the absolute distance of the player 
with the archer in the x and y axis , and find the angle using the arctan.*/
void Arrow::init()
{
	m_brush_arrow.fill_opacity = 1.0f;
	m_brush_arrow.outline_opacity = 0.0f;
	m_brush_arrow.texture = m_path_left;

	flag_x = m_state->getPlayer()->m_pos_x - m_archer->m_pos_x <= 0;
	flag_y = m_state->getPlayer()->m_pos_y - m_archer->m_pos_y<0;

	float distance_a = m_state->getPlayer()->m_pos_x - m_archer->m_pos_x;
	float distance_b = m_state->getPlayer()->m_pos_y - m_archer->m_pos_y;
	
	m_angle = std::atan2(fabs(distance_b), fabs(distance_a));

}

Arrow::Arrow(float x, float y, float width, float height,Archer* archer):Box(x,y,width,height)
{
	m_archer = archer;
}


