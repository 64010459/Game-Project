#include "Enemy4.h"

void Enemy4::initVariables()
{
	this->pointCount = 8;
	this->speed = 1.75;
	this->hpMax = 8;
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->score = this->pointCount;
}

void Enemy4::initTexture()
{
	//Load a texture from file
	this->texture.loadFromFile("Texture/cat level 3.png");
}

void Enemy4::initSprite()
{
	this->cat4.setTexture(this->texture);

	//Resize the sprite
	this->cat4.scale(0.2f, 0.2f);
}


Enemy4::Enemy4(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();

	this->cat4.setPosition(pos_x, pos_y);
}

Enemy4::~Enemy4()
{
}

const sf::FloatRect Enemy4::getBounds() const
{
	return this->cat4.getGlobalBounds();
}

const int& Enemy4::getScore() const
{
	return this->score;
}

const int& Enemy4::getDamage() const
{
	return this->damage;
}

//Functions
void Enemy4::update()
{
	this->cat4.move(0.f, this->speed);
}

void Enemy4::render(sf::RenderTarget* target)
{
	target->draw(this->cat4);
}
