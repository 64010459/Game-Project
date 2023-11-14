#include "Enemy2.h"

void Enemy2::initVariables()
{
	this->pointCount	= 6;
	this->speed			= 1.5;
	this->hpMax			= 6;
	this->hp			= this->hpMax;
	this->damage		= this->pointCount;
	this->score		= this->pointCount;
}

void Enemy2::initTexture()
{
	//Load a texture from file
	this->texture.loadFromFile("Texture/cat level 2.png");
}

void Enemy2::initSprite()
{
	this->cat2.setTexture(this->texture);

	//Resize the sprite
	this->cat2.scale(0.19f, 0.19f);
}

Enemy2::Enemy2(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();

	this->cat2.setPosition(pos_x, pos_y);
}

Enemy2::~Enemy2()
{
}

const sf::FloatRect Enemy2::getBounds() const
{
	return this->cat2.getGlobalBounds();
}

const int& Enemy2::getScore() const
{
	return this->score;
}

const int& Enemy2::getDamage() const
{
	return this->damage;
}

void Enemy2::update()
{
	this->cat2.move(0.f, this->speed);
}

void Enemy2::render(sf::RenderTarget* target)
{
	target->draw(this->cat2);
}
