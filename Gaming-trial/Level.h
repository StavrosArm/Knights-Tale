#pragma once
#include "Player.h"
#include <sgg/graphics.h>
#include "GameState.h"
#include <list>
#include "GameState.h"
#include "Platform.h"
#include "sword.h"

/*
H level περιέχει το brush που είναι υπεύθυνο για το background του παιχνιδιού . Επιπλεόν περιέχει δύο δομές δεδομένων m_static_objects,
m_dynamic_objects οι οποίες είναι υπεύθυνες για τα στατικά και δυναμικά αντικείμενα αντιστοίχως. Περιέχει και 3 δείκτες ,
δύο τύπου GameObject υπεύθυνους για το shop και τον death_bringer και έναν τύπου Sword .
Από μεθόδους σαν ιδιωτικές μεθόδους υλοποιήει μια μέθοδο υπεύθυνη για τα collisions και δύο υπεύθυνες για την αρχικοποιήση των 
δυναμικών και στατικών αντικειμένων μέσω δύό αρχείων csv.
Σαν δημοσίες μεθόδους έχει την GarbageCollection που διαγράδει ό,τι δημιουργείται δυναμικά, την followPlayer που είναι υπεύθυνη 
ώστε τα enemies να ακολουθούν τον player και notify_sword που ενεργοποιήει το σπαθί όταν σκοτώσει ο player τον death_bringer(final Boss)
*/

class Level :public GameObject
{
	graphics::Brush m_brush_background;
	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	std::vector<GameObject*>m_static_objects;
	std::list<GameObject*>m_dynamic_objects;
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