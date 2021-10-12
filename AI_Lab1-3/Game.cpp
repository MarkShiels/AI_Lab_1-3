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
	m_player.setSpeed(m_playerSpeed);
	m_npc.setTetxure(&m_alienTxtr);
	m_npc.setSpeed(m_npcSpeed);
	m_pi = 2 * acos(0.0);

	do {
		srand(time(0));
		float randX = (rand() % 20) - 10;
		float randY = (rand() % 20) - 10;
		float randX2 = (rand() % 20) - 10;
		float randY2 = (rand() % 20) - 10;
		m_npcVec = sf::Vector2f(randX2, randY2);
		normalise(m_npcVec);
		m_playerVec = sf::Vector2f(randX, randY);
		normalise(m_playerVec);
	} while (m_playerVec == sf::Vector2f(0,0) || m_npcVec == sf::Vector2f(0,0));

	m_player.setMoveVec(m_playerVec);
	m_npc.setMoveVec(m_npcVec);
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
	if (event.key.code == sf::Keyboard::Up && m_player.getSpeed() < 5.0f)
	{
		m_player.setSpeed(m_player.getSpeed() + 0.5f);
	}
	else if (event.key.code == sf::Keyboard::Down && m_player.getSpeed() > 0.5f )
	{
		m_player.setSpeed(m_player.getSpeed() - 0.5f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//event.key.code == sf::Keyboard::Left)
	{
		sf::Vector2f pVec = sf::Vector2f(m_player.getMoveVec());
		sf::Vector2f newVec;

		newVec.x = (pVec.x * cos(m_pi/36) + pVec.y * sin(m_pi / 36));
		newVec.y = (pVec.y * cos(m_pi / 36) - pVec.x * sin(m_pi / 36));

		m_player.setMoveVec(newVec);
	}

	if (event.key.code == sf::Keyboard::Right)
	{
		sf::Vector2f pVec = sf::Vector2f(m_player.getMoveVec());
		sf::Vector2f newVec;

		newVec.x = (pVec.x * cos(m_pi / 36) - pVec.y * sin(m_pi / 36));
		newVec.y = (pVec.y * cos(m_pi / 36) + pVec.x * sin(m_pi / 36));

		m_player.setMoveVec(newVec);
	}

}

void Game::update(sf::Time t_tpf)
{
	m_player.update(m_pi);
	m_npc.update(m_pi);

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

sf::Vector2f Game::normalise(sf::Vector2f t_vec)
{
	float vecMag = sqrt((t_vec.x * t_vec.x) + (t_vec.y * t_vec.y));

	sf::Vector2f returnVec = sf::Vector2f(t_vec.x / vecMag, t_vec.y / vecMag);

	return returnVec;
}
void Game::render()
{
	m_window.clear(sf::Color(255,255,255));

	m_player.render(&m_window);
	m_npc.render(&m_window);

	m_window.display();
}


