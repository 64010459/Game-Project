#pragma once

#include<map>
#include<string>
#include<sstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Item.h"
#include "ScoreList.h"

#define MENU_STATE 0
#define GAME_STATE 1
#define GAMEOVER_STATE 2
#define SCORE_BOARD 3
#define HOW_TO_PLAY 4

class Game {

private:

	ScoreList* score_list;

    unsigned short game_state;
    sf::RenderWindow* window;

    //Resources
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	sf::Text nameText;

	sf::Text text;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	sf::Texture menuBGTex;
	sf::Sprite menuBG;

	sf::Texture gameoverTex;
	sf::Sprite gameoverSprite;

	sf::Texture scoreBGTex;
	sf::Sprite scoreBG;

	sf::Texture howToPlayTex;
	sf::Sprite howToPlay;

	std::string enter_name = "";

	//Systems
	unsigned score;

	//Player
	Player* player;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;

	float spawnItem;
	float spawnItemMax;

	std::vector<Enemy*> enemies;
	std::vector<Enemy2*> enemies2;
	std::vector<Enemy3*> enemies3;
	std::vector<Enemy4*> enemies4;
	std::vector<Item*> items;

	void gameRestart();

	//Private functions
	void initTextures();
	void initMenu();
	void initGUI();
	void initWorld();
	void initSystems();
	void initPlayer();
	void initEnemies();

    void gameMenu();
    void gameMenuDraw();

    void gamePlay();
    void gamePlayDraw();

    void gameOver();
    void gameOverDraw();

	void scoreboardUpdate();
	void scoreboardDraw();

	void howtoplay();
	void howtoplayDraw();

public:

    Game(ScoreList* score_List);
    ~Game();

	void run();

	void updateInput();
	void updateGUI();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
    void update();
    void draw();

};
