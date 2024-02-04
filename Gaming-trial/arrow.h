#pragma once
#include "GameObject.h"
#include "GameState.h"
#include "Box.h"

class Arrow :public GameObject, public Box
{
	graphics::Brush m_brush_arrow;
	graphics::Brush m_brush_debug;
	graphics::Brush m_brush_coordinates;
	class Archer* m_archer;
	std::string m_path=m_state->getFullAssetPath("ArcherHero/Basic Arrow.png");
	std::string m_path_left = m_state->getFullAssetPath("ArcherHero/Basic Arrow_left.png");
	float m_angle = 0.0f;
	bool flag_x;
	bool flag_y;
public:
	void update(float dt ) override;
	void draw() override;
	void init() override;
	Arrow(float x, float y, float width, float height , Archer* archer);
	
};
