#include "Enemy3.h"

void Enemy3::initVariables()
{
	this->pointCount	= 10;
	this->speed			= 2;
	this->hpMax			= 10;
	this->hp			= this->hpMax;
	this->damage		= this->pointCount;
	this->score		= this->pointCount;
}

void Enemy3::initTexture()
{
	//Load a texture from file
	this->texture.loadFromFile("Texture/cat boss.png");
}

void Enemy3::initSprite()
{
	this->cat3.setTexture(this->texture);

	//Resize the sprite
	this->cat3.scale(0.2f, 0.2f);
}

Enemy3::Enemy3(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();

	this->cat3.setPosition(pos_x, pos_y);
}

Enemy3::~Enemy3()
{
}

const sf::FloatRect Enemy3::getBounds() const
{
	return this->cat3.getGlobalBounds();
}

const int& Enemy3::getScore() const
{
	return this->score;
}

const int& Enemy3::getDamage() const
{
	return this->damage;
}

void Enemy3::update()
{
	this->cat3.move(0.f, this->speed);
}

void Enemy3::render(sf::RenderTarget* target)
{
	target->draw(this->cat3);
}

