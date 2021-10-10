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

float Player::bodyWidth()
{
	return 0.0f;
}

float Player::bodyHeight()
{
	return 0.0f;
}

void Player::setTetxure(sf::Texture* t_txtr)
{
	body.setTexture(*t_txtr);
}

void Player::render(sf::RenderWindow* t_window)
{
	t_window->draw(body);
}