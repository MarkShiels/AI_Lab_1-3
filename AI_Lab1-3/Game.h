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
	void keyEvents(sf::Event event);
	void update(sf::Time t_tpf);
	void playerCheck();
	void npcCheck();
	void render();
	void playerFacing();

	float screenSize = sf::VideoMode::getDesktopMode().height / 1.5f;

	sf::RenderWindow	m_window;
	Player				m_player;
	NPC					m_npc;
	sf::Texture			m_playerTxtr;
	sf::Texture			m_alienTxtr;
	sf::Vector2f		m_playerVec;
	sf::Vector2f		m_npcVec;
	float				m_playerSpeed{1};
	float				m_npcSpeed{1};
	float				m_pi;

};

