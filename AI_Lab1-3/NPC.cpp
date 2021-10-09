#include "NPC.h"

NPC::NPC()
{
	body.setPosition(550, 550);
	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(62, 62));
}

NPC::~NPC()
{
}

void NPC::render(sf::RenderWindow* t_window)
{
	t_window->draw(body);
}
