#pragma once
#include <SFML/Graphics.hpp>
#include "Behaviour.h"

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
	void			setSpeed(float t_speed);
	float			getSpeed();
	void			setMoveVec(sf::Vector2f t_moveVec);
	sf::Vector2f	getMoveVec();
	void			update(float t_pi, sf::Vector2f t_target, sf::Vector2f t_targetVel);
	void			changeBehaviour(Behaviour t_b);
	void			boundaryCheck(float t_screenSize);
	bool			getDrawNoDraw();
	void			toggleDraw();
	void			setText(std::string t_text);
	std::string		getText();

private:

	Behaviour		behaviour;
	sf::Sprite		body;
	sf::Texture		bodyTxtr;
	sf::Vector2f	moveVec;
	float			speed;
	bool			drawNoDraw{false};
	void			facing(float t_pi);
	void			knmtcWander(float t_pi);
	void			seek(sf::Vector2f t_target);
	void			arrive(sf::Vector2f t_target);
	void			flee(sf::Vector2f t_target);
	void			pursue(sf::Vector2f t_target, sf::Vector2f t_targetVel);
	void			move();
	float			vectorMagnitude(sf::Vector2f t_vec);
	sf::Vector2f	normaliseVector(sf::Vector2f t_vec);
	std::string		label;
	sf::CircleShape cov;
};