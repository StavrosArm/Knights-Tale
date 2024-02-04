#include <iostream>
#include "sgg/graphics.h"
#include <string>
#include "GameState.h"



void init()
{
	GameState::getInstance()->init();
}

void draw() 
{
	
	GameState::getInstance()->draw();
}

void update(float dt)
{
	
	GameState::getInstance()->update(dt);
	
}



int main() {

	graphics::createWindow(800, 600,"A Knight's Tale");
	graphics::playMusic(GameState::getInstance()->getFullAssetPath("main_menu.wav"), 0.5f);
	init();
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);


	graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	

	graphics::startMessageLoop();
	
	return 0;
}






