#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:

	Player();
	~Player();

	void render(sf::RenderWindow* t_window);

private:

	sf::RectangleShape body;
};