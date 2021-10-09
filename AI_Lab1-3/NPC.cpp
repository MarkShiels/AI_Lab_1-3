#include "NPC.h"

NPC::NPC()
{
	body.setPosition(550, 550);
	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(62, 62));
	body.setOrigin(31, 31);
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

float NPC::bodyWidth()
{
	return body.getSize().x;
}

float NPC::bodyHeight()
{
	return body.getSize().y;
}

void NPC::render(sf::RenderWindow* t_window)
{
	t_window->draw(body);
}
