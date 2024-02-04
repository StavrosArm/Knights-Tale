#pragma once
#include "GameObject.h"
#include "box.h"
#include <sgg/graphics.h>

class Platform : public GameObject, public Box
{
private:
	graphics::Brush m_brush_platform;
	graphics::Brush m_brush_platform_debug;
public:

	void update(float dt) override;
	void init() override;
	void draw() override;
	
};

