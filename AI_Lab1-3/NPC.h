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
	void			setSpeed(float t_speed);
	float			getSpeed();
	void			setMoveVec(sf::Vector2f t_moveVec);
	sf::Vector2f	getMoveVec();
	void			move();
	void			facing(float t_pi);
	void			update(float t_pi);

private:

	sf::Sprite		body;
	sf::Texture		bodyTxtr;
	sf::Vector2f	moveVec;
	float			speed;
};