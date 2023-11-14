#ifndef ITEM_H
#define ITEM_H

#include<SFML/Graphics.hpp>

class Item
{
private:
	unsigned pointCount;
	sf::Texture texture;
	sf::Sprite cheese;
	int type;
	float speed;
	int hp;
	int hpMax;
	int heal;
	int score;

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Item(float pos_x, float pos_y);
	virtual ~Item();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getHeal() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif //!ITEM_H