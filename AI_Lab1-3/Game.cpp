#include "Game.h"
#include <iostream>

Game::Game() : m_window(sf::VideoMode(screenSize, screenSize, 32), "AI_Lab_1-3", sf::Style::Close)
{
	if (!m_playerTxtr.loadFromFile("Assets/playerShip.png"))
	{
		std::cout << "Can't load player ship" << std::endl;
	}
	if (!m_alienTxtr.loadFromFile("Assets/alienShip.png"))
	{
		std::cout << "Can't load alien ship" << std::endl;
	}

	m_player.setTetxure(&m_playerTxtr);
	m_npc.setTetxure(&m_alienTxtr);
	m_player.setRotation(90);
	m_pi = 2 * acos(0.0);

	do {
		srand(time(0));
		float randX = (rand() % 20) - 10;
		float randY = (rand() % 20) - 10;
		float randX2 = (rand() % 20) - 10;
		float randY2 = (rand() % 20) - 10;
		m_playerVec = sf::Vector2f(randX, randY);
		m_npcVec = sf::Vector2f(randX2, randY2);
	} while (m_playerVec == sf::Vector2f(0,0) || m_npcVec == sf::Vector2f(0,0));

}

Game::~Game()
{}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 30.f);

	while (m_window.isOpen())
	{

		timeSinceLastUpdate += clock.restart();

		processEvents();

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate = sf::Time::Zero;
			update(timePerFrame);
		}
		render();
	}

}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			keyEvents(event);
		}
	}

}

void Game::keyEvents(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Up && m_playerSpeed < 5.0f)
	{
		m_playerSpeed += 0.5f;
	}
	else if (event.key.code == sf::Keyboard::Down && m_playerSpeed > 0.0f )
	{
		m_playerSpeed -= 0.5f;
	}
}

void Game::update(sf::Time t_tpf)
{
	m_player.setPosition(m_player.getPosition() + (m_playerVec * m_playerSpeed));
	m_npc.setPosition(m_npc.getPosition() + (m_npcVec * m_npcSpeed));

	playerCheck();
	npcCheck();
}

void Game::playerCheck()
{
	if (m_player.getPosition().x < 0)
	{
		m_player.setPosition(sf::Vector2f(screenSize, m_player.getPosition().y));
	}
	else if (m_player.getPosition().x > screenSize)
	{
		m_player.setPosition(sf::Vector2f(0 , m_player.getPosition().y));
	}

	if (m_player.getPosition().y < 0)
	{
		m_player.setPosition(sf::Vector2f(m_player.getPosition().x, screenSize ));
	}
	else if (m_player.getPosition().y > screenSize)
	{
		m_player.setPosition(sf::Vector2f(m_player.getPosition().x, 0 ));
	}

	playerFacing();
}

void Game::npcCheck()
{
	if (m_npc.getPosition().x + m_npc.bodyWidth() < 0)
	{
		m_npc.setPosition(sf::Vector2f(screenSize + m_npc.bodyWidth(), m_npc.getPosition().y));
	}
	else if (m_npc.getPosition().x - m_npc.bodyWidth() > screenSize)
	{
		m_npc.setPosition(sf::Vector2f(0 - m_npc.bodyWidth(), m_npc.getPosition().y));
	}

	if (m_npc.getPosition().y + m_npc.bodyHeight() < 0)
	{
		m_npc.setPosition(sf::Vector2f(m_npc.getPosition().x, screenSize + m_npc.bodyHeight()));
	}
	else if (m_npc.getPosition().y - m_npc.bodyHeight() > screenSize)
	{
		m_npc.setPosition(sf::Vector2f(m_npc.getPosition().x, 0 - m_npc.bodyHeight()));
	}
}

void Game::playerFacing()
{
	float pX = m_player.getPosition().x;
	float pY = m_player.getPosition().y;

	float mX = m_playerVec.x;
	float mY = m_playerVec.y;

	float angle = atan2f((mY - pY), (mX - pX));
	angle = angle * (180 / m_pi);
	
	m_player.setRotation(angle);
}

void Game::render()
{
	m_window.clear(sf::Color(255,255,255));

	m_player.render(&m_window);
	m_npc.render(&m_window);

	m_window.display();
}

