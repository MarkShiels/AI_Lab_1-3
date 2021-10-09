#include "Player.h"

Player::Player()
{
	body.setPosition(200, 200);
	body.setFillColor(sf::Color::Blue);
	body.setSize(sf::Vector2f(62, 62));
}

Player::~Player()
{
}

void Player::render(sf::RenderWindow* t_window)
{
	t_window->draw(body);
}
