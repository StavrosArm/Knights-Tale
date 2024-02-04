#pragma once
#include "Player.h"
#include <sgg/graphics.h>
#include "GameState.h"
#include <list>
#include "GameState.h"
#include "Platform.h"
#include "sword.h"

class Level :public GameObject
{
	graphics::Brush m_brush_background;
	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	std::vector<GameObject*>m_static_objects;
	std::list<GameObject*>m_dynamic_objects;
	Platform m_platform;
	GameObject* shop;
	GameObject* death_bringer=nullptr;
	Sword* sword;

	void checkCollisions();
	void readDynamicFile(std::string dynamic_objects_file);
	void readStaticFile(std::string static_objects_file);
public:
	Level(const std::string& name = "Level0");
	~Level();
	void update(float dt) override;
	void GarbageCollection();
	void init() override;
	void draw() override;
	void followPlayer();

	void notify_sword();
};