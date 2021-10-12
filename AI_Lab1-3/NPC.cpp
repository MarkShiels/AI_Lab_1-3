#include "NPC.h"

NPC::NPC()
{
	body.setPosition(550, 550);
	body.setOrigin(106, 118.5);
	body.setScale(0.2, 0.2);
}

NPC::~NPC()
{
}

void NPC::setPosition(sf::Vector2f t_pos)
{
	body.setPosition(t_pos);
}

sf::Vector2f NPC::getPosition()
{
	return body.getPosition();
}

sf::Sprite NPC::getBody()
{
	return body;
}

void NPC::setTetxure(sf::Texture* t_txtr)
{
	body.setTexture(*t_txtr);
}

float NPC::bodyWidth()
{
	return 0.0f;
}

float NPC::bodyHeight()
{
	return 0.0f;
}

void NPC::setSpeed(float t_speed)
{
	speed = t_speed;
}

float NPC::getSpeed()
{
	return speed;
}

void NPC::setMoveVec(sf::Vector2f t_moveVec)
{
	moveVec = t_moveVec;
}

sf::Vector2f NPC::getMoveVec()
{
	return moveVec;
}

void NPC::move()
{
	body.move(moveVec * speed);
}

void NPC::facing(float t_pi)
{
	float pX = body.getPosition().x;
	float pY = body.getPosition().y;

	float mX = pX + moveVec.x;
	float mY = pY + moveVec.y;

	float angle = atan2f((mY - pY), (mX - pX));
	angle = angle * (180 / t_pi);

	body.setRotation(angle + 90);
}

void NPC::update(float t_pi)
{
	move();
	facing(t_pi);
}


void NPC::render(sf::RenderWindow* t_window)
{
	t_window->draw(body);
}
