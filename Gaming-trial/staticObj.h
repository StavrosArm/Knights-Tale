#pragma once
#include <iostream>
#include "GameObject.h"
#include "box.h"
#include "player.h"
#include <sgg/graphics.h>

class staticObj :public Box, public GameObject
{
protected:
	graphics::Brush m_staticObj_br;
	graphics::Brush m_staticObj_br_debug;
	float m_staticObj_size = 1.0f;
public:
	void update(float dt) override;
	void drawDebug() override;
	void init() override;
	void draw() override;
	staticObj(float x, float y, float width, float height, float m_staticObj_size);
};