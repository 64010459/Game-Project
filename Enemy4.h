#ifndef ENEMY4_H
#define ENEMY4_H

#include<SFML/Graphics.hpp>

class Enemy4
{
private:
	unsigned pointCount;
	sf::Texture texture;
	sf::Sprite cat4;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int score;

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Enemy4(float pos_x, float pos_y);
	virtual ~Enemy4();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getScore() const;
	const int& getDamage() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif //!ENEMY4_H
