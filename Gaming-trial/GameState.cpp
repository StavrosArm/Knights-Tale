#include "GameState.h"
#include "Level.h"
#include <thread>
#include <chrono>
#include <iostream>

GameState::GameState() {
	
}

void GameState::updateStartScreen(float dt)
{
	if(graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_PLAYING;
	}
	
}

void GameState::updateLevelScreen(float dt)
{
	
	if (dt > 500)
		return;

	float sleep_time = std::max(0.0f, 20.0f - dt);
	std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));

	if (!m_current_level)
		return;

	if ((getPlayer()->isActive())&&(notify_win)) {
		m_current_level->update(dt);
	}
	else if(!getPlayer()->isActive()) {
		updateFinalScreen(dt);
	}
	else {
		status = STATUS_WIN;
	}
		
	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);

}

void GameState::updateFinalScreen(float dt)
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		delete m_current_level;
		delete m_player;
		notify_win = true;
		init();

		status = STATUS_PLAYING;
	}
	 else if(graphics::getKeyState(graphics::SCANCODE_M))
	{
		delete m_current_level;
		delete m_player;
		init();
		status = STATUS_START;
	}
}

void GameState::updateWinScreen(float dt)
{
	
	if (graphics::getKeyState(graphics::SCANCODE_M))
	{
		notify_win = true;
		delete m_current_level;
		delete m_player;
		init();
		status = STATUS_START;
	}
}

void GameState::update(float dt)
{
	if (status == STATUS_START) {
		updateStartScreen(dt);
	}
	else if (status == STATUS_PLAYING)
	{
		updateLevelScreen(dt);
	}
	else {
		updateWinScreen(dt);
	}

}

void GameState::drawStartScreen()
{
	float w = getCanvasWidth();
	float h = getCanvasHeight();

	float offset_x = getCanvasWidth() / 2.0f; 
	float offset_y = getCanvasHeight() / 2.0f; 

	
	
	
	graphics::Brush m_brush_background;
	m_brush_background.texture = bridge[0];

	graphics::drawRect(offset_x, offset_y, w+1.f , h+1.f , m_brush_background);
	graphics::Brush br;
	br.fill_color[1] = 1.0f;
	graphics::drawText(getCanvasWidth()/2.f-3.f, getCanvasHeight()-1.f, 0.5f, "PRESS ENTER TO START", br);
	graphics::drawText(getCanvasWidth() / 2.f - 5.5f, 2.f,1.5f, "A Knight's Tale", br);

	graphics::Brush br2;
	br2.fill_opacity = 1.0f;
	br2.outline_opacity = 0.0f;
	br2.texture = bridge[1];
	graphics::drawRect(getCanvasWidth() / 2.f, getCanvasHeight() / 2.f, 8.f, 8.f, br2);
	
}

void GameState::drawLevelScreen()
{

	if (!m_current_level) {
		return;
	}

	if (getPlayer()->isActive()&&(notify_win)){
		m_current_level->draw();
	}
	else if (!getPlayer()->isActive()) {
		m_current_level->draw();
		drawFinalScreen();
	}



}

void GameState::drawFinalScreen() {
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	graphics::drawText(getCanvasWidth() / 2.f - 2.f, getCanvasHeight() / 2.f - 3.f, 0.5f, "PRESS ENTER TO RETRY", br);
	graphics::drawText(getCanvasWidth() / 2.f - 5.f, getCanvasHeight() / 2.f - 1.f, 2.f, "GAME OVER", br);
	graphics::drawText(getCanvasWidth() / 2.f - 2.f, getCanvasHeight() / 2.f, 0.5f, "PRESS M FOR MAIN MENU", br);

}

void GameState::drawWinScreen() {

	

	float offset_x = getCanvasWidth() / 2.0f; 
	float offset_y = getCanvasHeight() / 2.0f; 

	float w = getCanvasWidth();
	float h = getCanvasHeight();

	graphics::Brush m_brush_background;
	m_brush_background.texture = m_win_screen[0];
	m_brush_background.texture = getFullAssetPath("Bridge 2.png");
	graphics::drawRect(offset_x, offset_y, w + 1.f, h + 1.f, m_brush_background);

	graphics::Brush br2;
	br2.fill_opacity = 1.0f;
	br2.outline_opacity = 0.0f;
	br2.texture = m_win_screen[1];
	graphics::drawRect(getCanvasWidth() / 2.f, getCanvasHeight() / 2.f, 4.f, 4.f, br2);

	graphics::Brush br;
	br.fill_color[1] = 1.0f;
	graphics::drawText(getCanvasWidth() / 2.f - 2.5f, getCanvasHeight() - 1.f, 0.5f, "PRESS M FOR MAIN MENU", br);
	graphics::drawText(getCanvasWidth() / 2.f - 4.f, 2.f, 0.5f, "The sword of faith is now yours", br);


}

void GameState::draw()
{
	if (status == STATUS_START) {
		drawStartScreen();

	}
	else if (status == STATUS_PLAYING)
	{
		drawLevelScreen();
	}
	else {
		drawWinScreen();
	}
}

GameState* GameState::getInstance()
{

	if (m_unique_instance == nullptr) {
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

GameState::~GameState()
{
	if (m_player)
		delete m_player;
	if (m_current_level)
		delete m_current_level;
}



void GameState::init()
{
	
	DecorationsPaths = graphics::preloadBitmaps(getAssetDir() + "oak_woods_v1.0/decorations");
	graphics::setFont(getAssetDir() + "fonts/orange_juice_2.0.ttf");

	m_current_level = new Level("Level1");
	m_current_level->init();

	m_player = new Player("Player");
	m_player->init();
	
	m_win_screen = ::graphics::preloadBitmaps(getFullAssetPath("win_screen"));

	
	bridge.push_back(getFullAssetPath("Bridge 2.png"));
	bridge.push_back(getFullAssetPath("papyrus.png"));

	
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}

void GameState::setWinStatus()
{
	status = STATUS_WIN;
}


GameState* GameState::m_unique_instance = nullptr;