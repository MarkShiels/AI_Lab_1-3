#include "Player.h"

Player::Player()
{
	body.setPosition(50, 50);
	body.setOrigin(85.5, 145.5);
	body.setScale(0.25, 0.25);
}

Player::~Player()
{
}

void Player::setPosition(sf::Vector2f t_pos)
{
	body.setPosition(t_pos);
}

sf::Vector2f Player::getPosition()
{
	return body.getPosition();
}

sf::Sprite Player::getBody()
{
	return body;
}

void Player::setRotation(float t_angle)
{
	body.setRotation(t_angle);
}

void Player::rotate(float t_angle)
{
	body.rotate(t_angle);
}

float Player::bodyWidth()
{
	return 0.0f;
}

float Player::bodyHeight()
{
	return 0.0f;
}

void Player::setSpeed(float t_speed)
{
	speed = t_speed;
}

float Player::getSpeed()
{
	return speed;
}

void Player::setMoveVec(sf::Vector2f t_moveVec)
{
	moveVec = t_moveVec;
}

sf::Vector2f Player::getMoveVec()
{
	return moveVec;
}

void Player::update(float t_pi)
{
	move();
	facing(t_pi);
}

void Player::move()
{
	body.setPosition(body.getPosition() + (moveVec * speed));
}

void Player::facing(float t_pi)
{
	float pX = body.getPosition().x;
	float pY = body.getPosition().y;

	float mX = pX + moveVec.x;
	float mY = pY + moveVec.y;

	float angle = atan2f((mY - pY), (mX - pX));
	angle = angle * (180 / t_pi);

	body.setRotation(angle + 90);
}

void Player::setTetxure(sf::Texture* t_txtr)
{
	body.setTexture(*t_txtr);
}

void Player::render(sf::RenderWindow* t_window)
{
	t_window->draw(body);
}