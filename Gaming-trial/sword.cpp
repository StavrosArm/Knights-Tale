#include "sword.h"
#include "player.h"
#include <iostream>

void Sword::update(float dt)
{
    if (m_state->getPlayer()->intersect(*this)) {
        if (m_available) {
            m_state->notify_win = false;
            std::cout << "Intersecting" << std::endl;
        }
     
   }
 
}

void Sword::draw()
{
    float x = m_pos_x + m_state->m_global_offset_x;
    float y = m_pos_y + m_state->m_global_offset_y;
    graphics::setOrientation(42.f);
    graphics::drawRect(x, y-1.f, 3.f, 3.f, m_brush_sword);
    graphics::resetPose();

    
 
   
}

void Sword::init()
{
    text = "You must kill the bringer of death to obtain the sword of faith.";
    m_brush_sword.fill_opacity = 1.0f;
    m_brush_sword.outline_opacity = 0.0f;
    m_brush_sword.texture = m_state->getFullAssetPath("sword.png");
  


}

bool Sword::getAvailability()
{
    return m_available;
}

void Sword::setAvailability(bool m_avail)
{
    m_available = m_avail;
}

Sword::Sword(float x, float y, float width, float height):Box(x,y,width,height)
{
}

