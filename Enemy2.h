#ifndef ENEMY2_H
#define ENEMY2_H

#include<SFML/Graphics.hpp>

class Enemy2
{
private:
	unsigned pointCount;
	sf::Texture texture;
	sf::Sprite cat2;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int score;

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Enemy2(float pos_x, float pos_y);
	virtual ~Enemy2();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getScore() const;
	const int& getDamage() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif //!ENEMY2_H