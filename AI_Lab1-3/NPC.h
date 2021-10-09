#pragma once
#include <SFML/Graphics.hpp>

class NPC
{
public:

	NPC();
	~NPC();

	void render(sf::RenderWindow* t_window);

private:

	sf::RectangleShape body;
};