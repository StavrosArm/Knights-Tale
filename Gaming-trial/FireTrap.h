#pragma once
#include <iostream>
#include "GameObject.h"
#include "box.h"
#include <sgg/graphics.h>
#include "staticObj.h"
#include "GameState.h"

class FireTrap : public staticObj
{
private:
	graphics::Brush m_fire_br;

public:
	std::string m_dialogButton = "StartMenu";
	void update(float dt) override;
	void drawDebug() override;
	void init() override;
	void draw() override;
	void checkcollision();
	FireTrap (float x, float y, float width, float height, float staticObjSize);
};