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

void NPC::render(sf::RenderWindow* t_window)
{
	t_window->draw(body);
}
