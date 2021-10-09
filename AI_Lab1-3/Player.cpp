#include "Player.h"

Player::Player()
{
	body.setPosition(200, 200);
	body.setFillColor(sf::Color::Blue);
	body.setSize(sf::Vector2f(62, 62));
	body.setOrigin(31, 31);
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

float Player::bodyWidth()
{
	return body.getSize().x;
}

float Player::bodyHeight()
{
	return body.getSize().y;
}

void Player::render(sf::RenderWindow* t_window)
{
	t_window->draw(body);
}