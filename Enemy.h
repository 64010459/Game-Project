#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>

class Enemy
{
private:
	unsigned pointCount;
	sf::Texture texture;
	sf::Sprite cat1;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int score;

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getScore() const;
	const int& getDamage() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif //!ENEMY_H

