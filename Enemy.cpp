#include "Enemy.h"

void Enemy::initVariables()
{
	this->pointCount	= 3;
	this->speed			= 1;
	this->hpMax			= 3;
	this->hp			= this->hpMax;
	this->damage		= this->pointCount;
	this->score		= this->pointCount;
}

void Enemy::initTexture()
{
	//Load a texture from file
	this->texture.loadFromFile("Texture/cat level 1.png");
}

void Enemy::initSprite()
{
	this->cat1.setTexture(this->texture);

	//Resize the sprite
	this->cat1.scale(0.15f, 0.15f);
}


Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();

	this->cat1.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->cat1.getGlobalBounds();
}

const int& Enemy::getScore() const
{
	return this->score;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

//Functions
void Enemy::update()
{
	this->cat1.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->cat1);
}