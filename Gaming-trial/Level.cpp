#include "Level.h"
#include "GameState.h"
#include "GameObject.h"
#include <iostream>
#include"JumpRock.h"
#include "enemy.h"
#include "Shop.h"
#include "skeleton.h"
#include "Archer.h"
#include "coin.h"
#include "DeathBringer.h"
#include "FireTrap.h"
#include <fstream>
#include <sstream>


Level::Level(const std::string& name):GameObject(name)
{
}

/*The destructor.When the level's life comes to an end the destructor deletes all the remaining objects.*/
Level::~Level()
{
	for (auto p_gob : m_static_objects)
		if (p_gob) delete p_gob;
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) delete p_gob;
	delete shop;
	delete sword;
}


/*We've written all the coordinates and values of the dynamics objects 
in a csv in order to create and push back the objects to the dynamic_objects vector*/

void Level::readDynamicFile(std::string dynamic_objects_file)
{
	std::ifstream file(m_state->getFullAssetPath(dynamic_objects_file));
	if (!file.is_open()) {
		std::cerr << "Error opening dynamic objects file!" << std::endl;
	}
	std::string line;
	bool firstLine = true;
	while (std::getline(file, line)) {
		if (firstLine) {
			firstLine = false;
			continue;
		}
		std::istringstream ss(line);
		std::string token;
		std::vector<std::string>tokens;
		while (std::getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		float x = std::stof(tokens[0]);
		float y = std::stof(tokens[1]);
		float width = std::stof(tokens[2]);
		float height = std::stof(tokens[3]);
		std::string path = tokens[4];
		float hit_distanse = std::stof(tokens[5]);
		float life = std::stof(tokens[6]);
		std::string type = tokens[7];

		if (type == "Archer") {
			m_dynamic_objects.push_back(new Archer(x, y, width, height, path, hit_distanse, life));
		}
		else if (type == "Skeleton") {
			m_dynamic_objects.push_back(new Skeleton(x, y, width, height, path, hit_distanse, life));
		}
		else if (type == "Coin") {
			m_dynamic_objects.push_back(new Coin(x, y, width, height));
		}
		else if (type == "DeathBringer")
		{
			death_bringer = new DeathBringer(x, y, width, height, path, hit_distanse, life);
			m_dynamic_objects.push_back(death_bringer);
		}
	}
	file.close();

}

/*Same logic as the dynamic objects.*/
void Level::readStaticFile(std::string static_objects_file)
{
	
	
	std::ifstream file(m_state->getFullAssetPath(static_objects_file));
	if (!file.is_open()) {
		std::cerr << "Error opening static objects file!" << std::endl;
	}
	std::string line;
	bool firstLine = true;
	while (std::getline(file, line)) {
		if (firstLine) {
			firstLine = false;
			continue;
		}

		std::istringstream ss(line);
		std::string token;
		std::vector<std::string>tokens;

		while (std::getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		float x = std::stof(tokens[0]);
		float y = std::stof(tokens[1]);
		float width = std::stof(tokens[2]);
		float height = std::stof(tokens[3]);
		bool moveHorizontally = tokens[4] == "true";
		bool moveVertically = tokens[5] == "true";
		std::string type = tokens[6];
		
		if (type == "JumpRock") {
			m_static_objects.push_back(new JumpRock(x, y, width, height, moveHorizontally, moveVertically));
		}
		else if (type == "FireTrap")
		{
			for (int j = 3; j < 4; j++) {
				for (int i = x; i <= x+250; i++) {
					m_static_objects.push_back(new FireTrap(i, y + j, width, height, 1.0f));
					
				}
			}
		}

	}
	file.close();
}

/*We do all the nessecary updates , and we also call the garbage collector , 
to check if any objects are inactive.*/
void Level::update(float dt)
{
	
	if (m_state->getPlayer()->isActive())
	{
		m_state->getPlayer()->update(dt);
	}
	
	followPlayer();
	checkCollisions();
	GarbageCollection();
	sword->update(dt);
	shop->update(dt);
	
	for (auto p_gob : m_static_objects)
		if (p_gob->isActive()) p_gob->update(dt);
	for (auto p_gob : m_dynamic_objects) {
		if (p_gob->isActive()) {
			p_gob->update(dt);
		}	
	}
	if (!death_bringer->isActive()) {
		notify_sword();
	}
	
	GameObject::update(dt);
}

/*We delete the inactive GameObjects , by iterating through the 
dynamic_objects vector.*/
void Level::GarbageCollection() 
{
	auto it = m_dynamic_objects.begin();
	while (it != m_dynamic_objects.end()) {
		if (!(*it)->isActive()) {
			delete* it;
			it = m_dynamic_objects.erase(it);
		}
		else {
			++it;
		}
	}
}

/*The idea behind the followPlayer method is that any dynamic_object
that is an enemy , should follow the player within a certain range. By eyeballing it 
we decided.that if the distance is smaller than 5.f the enemy should follow the player.If there are intersecting , it means 
that they are fighting , in which case the Enemy class and the Player class takes care of the changes in frames and in lives.*/
void Level::followPlayer() 
{
	float check_x = m_state->getPlayer()->m_pos_x;
	float check_y = m_state->getPlayer()->m_pos_y;
	for (auto p_gob : m_dynamic_objects) {
		Box* enemy = dynamic_cast<Box*>(p_gob);
		if (dynamic_cast<Enemy*>(p_gob)) {

			if (p_gob->isActive()) {
				if (m_state->getPlayer()->intersect(*enemy))
				{
					break;
				}
				else {
					if ((fabs(enemy->m_pos_x - check_x) < 5.f) && (fabs(enemy->m_pos_x - check_x) > 1.4f))
					{

						enemy->m_pos_x -= ((enemy->m_pos_x - check_x) / (fabs(enemy->m_pos_x - check_x))) * 0.03f;
						
					}

					Enemy* en = dynamic_cast<Enemy*>(p_gob);
					en->followPlayer();
				}
			}
		}
	}

}

void Level::notify_sword()
{
	sword->setAvailability(true);
}

/*At this method we check the collsions , there are 3 main collisions we need to check.
Player with StaticObjects , Player with DynamicObjects(Enemies , Coins etc) and also the collisions
of dynamic objects with static ones.*/
void Level::checkCollisions()
{
	float offset = 0.0f;

	/*Player with StaticObjects.Some JumpRocks can move through the canvas (as they don't have a specific time to live 
	they are considered static objects). So in addition we check if the Player is intersecting with a moving objects , 
	and tune the player's position according to the period the trigonometric function used for moving the object uses.*/
	for (auto& p_gob : m_static_objects)
	{
		Box* StaticObject = dynamic_cast<Box*>(p_gob);

		float offset1 = 0.0f;
		float offset = 0.0f;
		float offset2 = 0.0f;
		
		if (offset = m_state->getPlayer()->intersectSideways(*StaticObject, 5 * (StaticObject->m_width) / 2.f))
		{
			m_state->getPlayer()->m_pos_x += offset;
			m_state->getPlayer()->m_vx = 0.0f;
			
			
		}
		

		if (offset2 = (StaticObject->intersectDown(*m_state->getPlayer())))
		{
			m_state->getPlayer()->m_pos_y -= (offset2);
			m_state->getPlayer()->m_vy = 1.0f;
		}
		

		if (offset1 = m_state->getPlayer()->intersectDown(*StaticObject))
		{

			if (FireTrap* firetrap = dynamic_cast<FireTrap*>(p_gob)) 
			{
				m_state->getPlayer()->life = 0.0f;
				break;
			}
			if (JumpRock* Object = dynamic_cast<JumpRock*>(p_gob)) {
				m_state->getPlayer()->m_pos_y += (offset1);
				m_state->getPlayer()->m_vy = 0.0f;
				if (Object->m_move_hor)
				{
					m_state->getPlayer()->m_pos_x -= Object->freq_move;
					
				}
				else if (Object->m_move_ver) {
					m_state->getPlayer()->m_pos_y += Object->freq_move+0.019f;
					
					
				}

			}


		}

	}

	/*There are 2 many dynamic objects, Enemies and Coins. When we intersect with a coin we want to set it inactive , 
	and also add 10$ to the player's wallet.*/
	for (auto p_gob_d : m_dynamic_objects)
	{
		if (p_gob_d->isActive()) {
			
			Box* enemy = dynamic_cast<Box*>(p_gob_d);
			float offest = 0.0f;
			if (offset = m_state->getPlayer()->intersectSideways(*enemy, 2.f)) {
				
				
				if (Coin* Object = dynamic_cast<Coin*>(p_gob_d))
				{
					p_gob_d->setActive(false);
					m_state->getPlayer()->addToWallet(10);
				}
				else {
					m_state->getPlayer()->m_pos_x += offset;
					m_state->getPlayer()->m_vx = 0.0f;
				}
			}

			/*We are checking the collisions of the dynamic object with the static ones.The enemies have their one m_gravity,
			so if the enemy is intersecting down with a platform we add the difference and zero it's velocity.In addition , 
			we make sure that if an enemy is positioned in a specific JumpRock would not get out of the JumpRock's range.*/
			for (auto p_gob : m_static_objects)
			{
				if (Box* StaticObject = dynamic_cast<Box*>(p_gob)) {


					float offset = 0;
					if (offset = enemy->intersectDown(*StaticObject))
					{

						enemy->m_pos_y += offset;
						if (Enemy* check = dynamic_cast<Enemy*>(p_gob_d))
							check->m_vy = 0.0f;
							

						if (enemy->m_pos_x <= StaticObject->m_pos_x - StaticObject->m_width / 2.f + 0.5f)
						{
							enemy->m_pos_x = StaticObject->m_pos_x - StaticObject->m_width / 2.f + 0.5f;
						}
						else if (enemy->m_pos_x >= StaticObject->m_pos_x + StaticObject->m_width / 2.f - 0.5f)
						{
							enemy->m_pos_x = StaticObject->m_pos_x + StaticObject->m_width / 2.f - 0.5f;
						}

						
						/*Collision's with moving JumpRocks and enemies.*/
						if (JumpRock* Object = dynamic_cast<JumpRock*>(p_gob)) {
							if (enemy->m_pos_x - Object->m_pos_x < Object->m_width / 2.f) {
								if (Object->m_move_hor)
								{
									enemy->m_pos_x -= Object->freq_move+0.002f;

								}
								else if (Object->m_move_ver) {
									enemy->m_pos_y += Object->freq_move + 0.03f;

								}

							}
						}
					
					}


					

					
				}

				
			}
		}
	}
}



/*We instantiate the static and dynamic objects of these level by calling readStaticFile/readDynamicFile , and we 
call the init() functions of the objects.*/
void Level::init()
{
	if (m_name == "Level1") {

		
		m_brush_background.outline_opacity = 0.0f;
		m_brush_background.texture = m_state->getAssetDir() + "Fortress 1.png";

		
		readStaticFile("static_objects_file.csv");
		readDynamicFile("dynamic_objects_file.csv");

		for (auto p_gob : m_static_objects)
			if (p_gob) p_gob->init();
		for (auto p_gob : m_dynamic_objects)
			if (p_gob) p_gob->init();
		
		shop = new Shop(23.f, 1.9f, 3.0f, 3.0f, 3.f);
		shop->init();

		sword = new Sword(50.f,-2.f,0.7f,0.8f);
		sword->init();

		

	}
}

/*The main draw function. It is responsible to draw the background , the logo , check the active objects and call their 
functions to.*/
void Level::draw()
{
	if (m_name == "Level1") {

		float w = m_state->getCanvasWidth();
		float h = m_state->getCanvasHeight();

		float offset_x = m_state->getCanvasWidth()/2.0f + m_state->m_global_offset_x;
		float offset_y = m_state->getCanvasHeight()/2.0f + m_state->m_global_offset_y;

		graphics::drawRect(offset_x, offset_y, w * 5.f, h * 2.5f, m_brush_background);
		
		shop->draw();
		sword->draw();
		if (m_state->getPlayer()) {
			m_state->getPlayer()->draw();
		}
		
		graphics::Brush br_title;
		br_title.fill_color[1] = 1.0f;
		graphics::drawText(m_state->getCanvasWidth() / 2.f-1.9f , 0.9f, 0.8f, "A Knight's Tale", br_title);
		
		
		for (auto p_gob : m_static_objects)
			if (p_gob->isActive()) p_gob->draw();
		for (auto p_gob : m_dynamic_objects)
			if (p_gob->isActive()) {
				p_gob->draw();	}
			
	}
}
