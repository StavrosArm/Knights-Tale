#pragma once
#include <iostream>
#include "GameObject.h"
#include "box.h"
#include <sgg/graphics.h>
#include "staticObj.h"
#include "GameState.h"

/*
	Το shop περιέχει 3 brushes τα οποία χρησιμοποιούνται στην drawText ώστε να γίνεται ο διάλογος με τον Player .
	Επιπλέον Χρησιμοποιούμε δύο ιδιωτικές μεταβλητές bool για να αντιμετωπίσω το πρόβλημα που προκύπτει όταν πατιέται ένα κουμπί.
	Αυτό εξασφαλίζει ότι η διαδικασία εκτελείται μια φορά όσο είναι πατημένο το κουμπί.
	Τέλος υλοποιούμε 5 βασικές μεθόδους που είναι υπευθύνες για την διαχείριση της αλληλεπίδρασης του player με το shop.
*/

class Shop :public staticObj
{
private:
	graphics::Brush m_br_text;
	graphics::Brush m_br_text1;
	graphics::Brush m_br_text2;
	std::string m_dialog_sting = "Hello ,Do you want to buy something ?[Y,N]";
	std::string m_dialog_string1;
	std::string m_dialog_string2;
	float m_text_x = m_state->getCanvasWidth() / 2.0f - 4.0f;
	float m_text_y = m_state->getCanvasHeight() / 2.0f - 2.5f;
	bool Press1Allowed;
	bool Press2Allowed;

public:
	std::string m_dialogButton = "StartMenu";
	void SetMainMenuStats();
	void SetElseMenuStats();
	void SetPreLastMenuStats();
	void SetLastMenuStats();
	void SetStartMenuStats();
	void update(float dt) override;
	void drawDebug() override;
	void init() override;
	void draw() override;
	Shop(float x, float y, float width, float height, float staticObjSize);
};