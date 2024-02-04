#pragma once 
#include "Box.h"
#include "GameState.h"
#include "GameObject.h"
#include "sgg/graphics.h"

class Sword :public GameObject, public Box 
{
	graphics::Brush m_brush_sword;
	graphics::Brush m_brush_text;

	std::string text;
	bool m_available = false;

public:
	void update(float dt) override;
	void draw() override;
	void init() override;

	bool getAvailability();
	void setAvailability(bool m_avail);
	Sword(float x, float y, float width, float height);


};