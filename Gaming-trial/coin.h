#pragma once
#include "sgg/graphics.h"
#include "GameObject.h"
#include "Box.h"
#include "GameState.h"



class Coin :public Box, public GameObject 
{
	graphics::Brush m_coin_brush;

	const std::string path = m_state->getFullAssetPath("coin");
	std::vector<std::string> m_coin_animations;
	const int m_value = 10;
public:
	void init() override;
	void update(float dt) override;
	void draw() override;
	Coin(float x , float y, float width, float height);
	int getValue();
};