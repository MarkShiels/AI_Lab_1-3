#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include "NPC.h"
#include "Player.h"

class Game
{

public:

			Game();
			~Game();
	void	run();


private:

	void processEvents();
	void update(sf::Time t_tpf);
	void render();

	sf::RenderWindow	m_window;
	Player				m_player;
	NPC					m_npc;

	sf::Vector2f		m_playerVec;
	sf::Vector2f		m_npcVec;
	float				m_playerSpeed;
	float				m_npcSpeed;

};

