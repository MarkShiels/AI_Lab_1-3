#pragma once
#include <SFML/Graphics.hpp>

class NPC
{
public:

	NPC();
	~NPC();

	void			render(sf::RenderWindow* t_window);
	void			setPosition(sf::Vector2f t_pos);
	sf::Vector2f	getPosition();
	sf::Sprite		getBody();
	void			setTetxure(sf::Texture* t_txtr);
	float			bodyWidth();
	float			bodyHeight();

private:

	sf::Sprite	body;
	sf::Texture	bodyTxtr;
};