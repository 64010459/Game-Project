#include "Item.h"

void Item::initVariables()
{
	this->pointCount = 10;
	this->type = 0;
	this->speed = 2;
	this->hpMax = 10;
	this->hp = this->hpMax;
	this->heal = this->pointCount;
}

void Item::initTexture()
{
	//Load a texture from file
	this->texture.loadFromFile("Texture/cheese.png");
}

void Item::initSprite()
{
	this->cheese.setTexture(this->texture);

	//Resize the sprite
	this->cheese.scale(0.2f, 0.2f);
}

Item::Item(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();

	this->cheese.setPosition(pos_x, pos_y);
}

Item::~Item()
{
}

const sf::FloatRect Item::getBounds() const
{
	return this->cheese.getGlobalBounds();
}

const int& Item::getHeal() const
{
	return this->heal;
}

void Item::update()
{
	this->cheese.move(0.f, this->speed);
}

void Item::render(sf::RenderTarget* target)
{
	target->draw(this->cheese);
}
