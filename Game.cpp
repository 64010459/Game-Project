#include "Game.h"
#include "ScoreList.h"

sf::Clock clock1sec;

void Game::gameRestart()
{
	score = 0;
	this->player->setHp(100);
	this->player->setPosition(340.f, 600.f);
	clock1sec.restart();
	this->enemies.clear();
	this->enemies2.clear();
	this->enemies3.clear();
	this->enemies4.clear();
	this->items.clear();
	this->bullets.clear();
	
	std::cout << "Restart" << std::endl;
}

////Private functions
void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Texture/platoo.png");
}

void Game::initMenu()
{
	if (!this->menuBGTex.loadFromFile("Texture/Menubackground.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD TEXTURE" << "\n";
	}

	this->menuBG.setTexture(this->menuBGTex);
}

void Game::initGUI()
{
	//Load font
	if (this->font.loadFromFile("Fonts/lookpeach.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	this->pointText.setPosition(660.f, 20.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color(161, 206, 211, 255));

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color(229, 92, 72, 255));
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f, 50.f);


	this->nameText.setFont(this->font);
	this->nameText.setCharacterSize(35);
	this->nameText.setFillColor(sf::Color(229, 92, 72, 255));
	this->nameText.setString("Please enter your name.\n\n\nPress Space to continue.");
	this->nameText.setPosition(
		this->window->getSize().x / 2.f - this->nameText.getGlobalBounds().width / 2.f, 
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	this->text.setFont(this->font);
	this->text.setCharacterSize(30);
	this->text.setFillColor(sf::Color(84, 118, 239, 255));

	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color(241, 187, 186, 255));
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Texture/world.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);

	if (!this->gameoverTex.loadFromFile("Texture/background.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->gameoverSprite.setTexture(this->gameoverTex);

	if (!this->scoreBGTex.loadFromFile("Texture/scoreBG.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->scoreBG.setTexture(this->scoreBGTex);

	if (!this->howToPlayTex.loadFromFile("Texture/howtoplay.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->howToPlay.setTexture(this->howToPlayTex);
}

void Game::initSystems()
{
	this->score = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 100.f;
	this->spawnTimer = this->spawnTimerMax;

	this->spawnItemMax = 100.f;
	this->spawnItem = this->spawnItemMax;
}

void Game::run()
{
	while(this->window->isOpen()) {
		
		this->update();
		this->draw();
	}
}



Game::Game(ScoreList* score_List)
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Mike the mouse", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);

	this->game_state = MENU_STATE;

	this->initTextures();
	this->initMenu();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initPlayer();
	this->initEnemies();

	this->score_list = score_List;
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//Delete Bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}

	//Delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}

	for (auto* i : this->enemies2)
	{
		delete i;
	}

	for (auto* i : this->enemies3)
	{
		delete i;
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f,
				this->player->getPos().y,
				0.f, -1.f, 5.f));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->score;

	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateCollision()
{
	//Left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	//Right world collision
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}

	//Down world collison
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}


void Game::updateBullets()
{
	unsigned counter = 0;

	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}
		++counter;
	}
}

void Game::updateEnemies()
{
	sf::Time t1;
	t1 = clock1sec.getElapsedTime();
	int num = (int)t1.asSeconds();

	//Spawning
	this->spawnTimer += 0.5f;

	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 40.f, -100.f));
		if (score >= 100)
			this->enemies2.push_back(new Enemy2(rand() % this->window->getSize().x - 40.f, -100.f));
		if (score >= 300)
			this->enemies4.push_back(new Enemy4(rand() % this->window->getSize().x - 40.f, -100.f));
		if (score >= 500)
			this->enemies3.push_back(new Enemy3(rand() % this->window->getSize().x - 50.f, -100.f));

		this->spawnTimer = 0.f;
	}

	this->spawnItem += 0.3f;

	if (this->spawnItem >= this->spawnItemMax)
	{
		if (num >= 20)
		{
			this->items.push_back(new Item(rand() % this->window->getSize().x - 50.f, -100.f));
		}
		this->spawnItem = 0.f;
	}

	//Update
	unsigned counter = 0;
	unsigned counter2 = 0;
	unsigned counter3 = 0;
	unsigned counter4 = 0;
	unsigned counter5 = 0;

	for (auto* enemy : this->enemies)
	{
		enemy->update();

		if (enemy->getBounds().top + enemy->getBounds().height >= this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}

		//Enemy player collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		++counter;
	}

	for (auto* enemy2 : this->enemies2)
	{
		enemy2->update();

		if (enemy2->getBounds().top + enemy2->getBounds().height >= this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies2.at(counter2);
			this->enemies2.erase(this->enemies2.begin() + counter2);
		}

		//Enemy player collision
		if (enemy2->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies2.at(counter2)->getDamage());
			delete this->enemies2.at(counter2);
			this->enemies2.erase(this->enemies2.begin() + counter2);
		}
		++counter2;
	}

	for (auto* enemy3 : this->enemies3)
	{
		enemy3->update();

		if (enemy3->getBounds().top + enemy3->getBounds().height >= this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies3.at(counter3);
			this->enemies3.erase(this->enemies3.begin() + counter3);
		}

		//Enemy player collision
		if (enemy3->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies3.at(counter3)->getDamage());
			delete this->enemies3.at(counter3);
			this->enemies3.erase(this->enemies3.begin() + counter3);
		}
		++counter3;
	}

	for (auto* enemy4 : this->enemies4)
	{
		enemy4->update();

		if (enemy4->getBounds().top + enemy4->getBounds().height >= this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies4.at(counter5);
			this->enemies4.erase(this->enemies4.begin() + counter5);
		}

		//Enemy player collision
		else if (enemy4->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies4.at(counter5)->getDamage());
			delete this->enemies4.at(counter5);
			this->enemies4.erase(this->enemies4.begin() + counter5);
		}
		++counter5;
	}

	for (auto* item : this->items)
	{
		item->update();

		if (item->getBounds().top + item->getBounds().height >= this->window->getSize().y)
		{
			//Delete item
			delete this->items.at(counter4);
			this->items.erase(this->items.begin() + counter4);

			clock1sec.restart();
		}

		//Item player collision
		else if (item->getBounds().intersects(this->player->getBounds()))
		{
			this->player->getHeal(this->items.at(counter4)->getHeal());
			delete this->items.at(counter4);
			this->items.erase(this->items.begin() + counter4);

			clock1sec.restart();
		}
		++counter4;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->score += this->enemies[i]->getScore();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}

	if (score >= 100) {
		for (int i = 0; i < this->enemies2.size(); ++i)
		{
			bool enemy2_deleted = false;
			for (size_t k = 0; k < this->bullets.size() && enemy2_deleted == false; k++)
			{
				if (this->enemies2[i]->getBounds().intersects(this->bullets[k]->getBounds()))
				{
					this->score += this->enemies2[i]->getScore();

					delete this->enemies2[i];
					this->enemies2.erase(this->enemies2.begin() + i);

					delete this->bullets[k];
					this->bullets.erase(this->bullets.begin() + k);

					enemy2_deleted = true;
				}
			}
		}
	}

	if (score >= 300) {
		for (int i = 0; i < this->enemies4.size(); ++i)
		{
			bool enemy4_deleted = false;
			for (size_t k = 0; k < this->bullets.size() && enemy4_deleted == false; k++)
			{
				if (this->enemies4[i]->getBounds().intersects(this->bullets[k]->getBounds()))
				{
					this->score += this->enemies4[i]->getScore();

					delete this->enemies4[i];
					this->enemies4.erase(this->enemies4.begin() + i);

					delete this->bullets[k];
					this->bullets.erase(this->bullets.begin() + k);

					enemy4_deleted = true;
				}
			}
		}
	}

	if (score >= 500) {
		for (int i = 0; i < this->enemies3.size(); ++i)
		{
			bool enemy3_deleted = false;
			for (size_t k = 0; k < this->bullets.size() && enemy3_deleted == false; k++)
			{
				if (this->enemies3[i]->getBounds().intersects(this->bullets[k]->getBounds()))
				{
					this->score += this->enemies3[i]->getScore();

					delete this->enemies3[i];
					this->enemies3.erase(this->enemies3.begin() + i);

					delete this->bullets[k];
					this->bullets.erase(this->bullets.begin() + k);

					enemy3_deleted = true;
				}
			}
		}
	}
}

void Game::update()
{
	if (this->game_state == MENU_STATE) gameMenu();
	if (this->game_state == GAME_STATE) gamePlay();
	if (this->game_state == GAMEOVER_STATE) gameOver();
	if (this->game_state == SCORE_BOARD) scoreboardUpdate();
	if (this->game_state == HOW_TO_PLAY) howtoplay();
}

void Game::draw()
{
	this->window->clear();

	if (this->game_state == MENU_STATE) gameMenuDraw();
	if (this->game_state == GAME_STATE) gamePlayDraw();
	if (this->game_state == GAMEOVER_STATE) gameOverDraw();
	if (this->game_state == SCORE_BOARD) scoreboardDraw();
	if (this->game_state == HOW_TO_PLAY) howtoplayDraw();

	this->window->display();
}

// UPDATE STATE
void Game::gameMenu()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		
		if(e.type == e.Event::TextEntered) {

			if (e.text.unicode == 32) { //Space
				
				game_state = GAME_STATE;
				gameRestart();
			}
			if (e.text.unicode == 13)//Enter
				game_state = SCORE_BOARD;

			if (e.text.unicode == 9) //Tab
				game_state = HOW_TO_PLAY;

			if (e.text.unicode == 27) //ESC
			this->window->close();
		}
	}
}
void Game::gamePlay()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		

		if(e.type == e.Event::TextEntered) {

			if (e.text.unicode == 13) { //Enter
				game_state = GAMEOVER_STATE;
			}
			
			if (e.text.unicode == 27)
			this->window->close();
		}
	}
	if (this->player->getHp() > 0)
	{
		this->updateInput();
		this->player->update();
		this->updateCollision();
		this->updateBullets();
		this->updateEnemies();
		this->updateCombat();
		this->updateGUI();
	}

	if (this->player->getHp() <= 0)
		game_state = GAMEOVER_STATE;
}
void Game::gameOver()
{
	sf::Event e;

	while (this->window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			this->window->close();
		
		if(e.type == e.Event::TextEntered) {
			if (e.text.unicode == 9) {//Tab
				game_state = GAME_STATE;
				gameRestart();
			}

			if (e.text.unicode == 27)
			this->window->close();

			// ลบตัวหนังสือ
			if (e.text.unicode == 8) { // ปุ่ม Backspace 

				if (enter_name.size() > 0) enter_name.erase(enter_name.end() - 1);
			}
			if ((e.text.unicode >= 'A' && e.text.unicode <= 'Z') ||
				(e.text.unicode >= 'a' && e.text.unicode <= 'z')) {

				if (enter_name.size() < 10) enter_name.push_back(e.text.unicode);
			}

			// กด Space เพื่อยืนยันเปลี่ยน State และ บันทึกคะแนน
			if (e.text.unicode == 32) {//Space
				if (enter_name.size() > 0) {
					score_list->addEntry(enter_name, score);
				}
				game_state = SCORE_BOARD;
			}
		}
	}
	this->text.setString(enter_name + "_");
	this->text.setPosition(this->window->getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f, 350.f);
}

void Game::scoreboardUpdate()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();

		if (e.type == e.Event::TextEntered) {

			if (e.text.unicode == 32) { //Space

				game_state = GAME_STATE;
				gameRestart();
			}
			if (e.text.unicode == 9) game_state = MENU_STATE;
		}
	}
}

void Game::howtoplay()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();

		if (e.type == e.Event::TextEntered) {

			if (e.text.unicode == 32) { //Space

				game_state = GAME_STATE;
				gameRestart();
			}
			if (e.text.unicode == 9) game_state = MENU_STATE; //Tab
		}
	}
}

// DRAW STATE
void Game::gamePlayDraw()
{
	sf::Time t1;
	t1 = clock1sec.getElapsedTime();
	int num = (int)t1.asSeconds();

	//Draw world
	this->window->draw(this->worldBackground);

	//Draw all stuffs
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* enemy2 : this->enemies2)
	{
		if (score >= 100)
			enemy2->render(this->window);
	}

	for (auto* enemy3 : this->enemies3)
	{
		if (score >= 500)
			enemy3->render(this->window);
	}

	for (auto* enemy4 : this->enemies4)
	{
		if (score >= 300)
			enemy4->render(this->window);
	}

	for (auto* item : this->items)
	{
		if (num >= 20) {
			item->render(this->window);
		}
	}

	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}
void Game::gameMenuDraw()
{
	this->window->draw(this->menuBG);
}

void Game::gameOverDraw()
{
	this->window->draw(this->gameoverSprite);
	this->window->draw(this->pointText);
	this->window->draw(this->gameOverText);
	this->window->draw(this->nameText);
	this->window->draw(this->text);
}

void Game::scoreboardDraw()
{
	this->window->draw(this->scoreBG);

	int max_entry = 5;
	for (int i = 0; i < score_list->get().size(); i++) {

		if (i >= max_entry) break;

		text.setPosition(240, 200 + (i * 40));
		text.setString(score_list->get().at(i).getName());
		this->window->draw(text);
	}
	for (int i = 0; i < score_list->get().size(); i++) {

		if (i >= max_entry) break;

		text.setPosition(512, 200 + (i * 40));
		text.setString(std::to_string(score_list->get().at(i).getScore()));
		this->window->draw(text);
	}
}

void Game::howtoplayDraw()
{
	this->window->draw(this->howToPlay);
}
