#ifndef ENEMY3_H
#define ENEMY3_H

#include<SFML/Graphics.hpp>

class Enemy3
{
private:
	unsigned pointCount;
	sf::Texture texture;
	sf::Sprite cat3;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int score;

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Enemy3(float pos_x, float pos_y);
	virtual ~Enemy3();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getScore() const;
	const int& getDamage() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif //!ENEMY3_H
