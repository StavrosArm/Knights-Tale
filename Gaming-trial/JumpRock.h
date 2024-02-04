#pragma once
#include <iostream>
#include "GameObject.h"
#include "box.h"
#include <sgg/graphics.h>

class JumpRock :public GameObject, public Box
{
private:
	graphics::Brush m_jumprock_br;
	graphics::Brush m_jumprock_br_debug;
	float JumpRocksize = 1.0f;
	int first_draw=0;
	float time_of_draw = 0.0f;
	
public:
	void update(float dt) override;
	void drawDebug() override;
	void init() override;
	void draw() override;
	JumpRock(float x, float y, float width, float height , bool move_horizontically=false, bool move_vertically=false );
	float freq_move=0.0f;
	bool m_move_hor;
	bool m_move_ver;
};
