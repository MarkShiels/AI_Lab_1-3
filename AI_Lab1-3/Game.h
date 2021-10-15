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

	void			processEvents();
	void			keyEvents(sf::Event event);
	void			update(sf::Time t_tpf);
	void			playerCheck();
	void			npcCheck();
	void			render();
	sf::Vector2f	normaliseVector(sf::Vector2f t_vec);

	float screenSize = sf::VideoMode::getDesktopMode().height / 1.5f;

	sf::RenderWindow	m_window;
	Player				m_player;
	NPC					m_npcWdr;
	NPC					m_npcSk;
	NPC					m_npcArv;
	NPC					m_npcFle;
	NPC					m_npcPrs;
	sf::Texture			m_playerTxtr;
	sf::Texture			m_alienTxtr;
	sf::Vector2f		m_playerVec;
	sf::Vector2f		m_npcVec;
	sf::Vector2f		m_npcVec2;

	float				m_playerSpeed{1};
	float				m_npcSpeed{4};
	float				m_npcSpeed2{ 2 };
	float				m_pi;

	std::vector<NPC>		m_aliens;
	sf::Font				m_font;
	std::vector<sf::Text>	m_text;
	sf::Text				m_text2;
	
};

