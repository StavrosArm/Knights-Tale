#pragma once
#include <string>
#include <sgg/graphics.h>
#include <vector>

class GameState
{
private:
	typedef enum {STATUS_START,STATUS_PLAYING,STATUS_WIN} status_t;
	std::string m_asset_path = "assets//";
	float m_canvas_width = 20.f;
	float m_canvas_height = 12.f;
	static GameState* m_unique_instance;
	status_t status=STATUS_START;
	GameState();
	class Player* m_player = 0;
	class Level* m_current_level = 0;

	void updateStartScreen(float dt);
	void updateLevelScreen(float dt);
	void updateFinalScreen(float dt);
	void updateWinScreen(float dt);

	void drawStartScreen();
	void drawWinScreen();
	void drawLevelScreen();
	void drawFinalScreen();
	

public:
	std::vector<std::string> DecorationsPaths;
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;
	bool m_debugging = false;
	static GameState* getInstance();
	~GameState();
	void init();
	void draw();
	void update(float dt);
	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }
	class Player* getPlayer() { return m_player; }
	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);

	std::vector<std::string> m_win_screen;
	std::vector<std::string> bridge;

	void setWinStatus();
	bool notify_win = true;
};