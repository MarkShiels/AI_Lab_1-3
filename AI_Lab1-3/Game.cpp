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

	m_npcWdr.setTetxure(&m_alienTxtr);
	m_npcWdr.setSpeed(m_npcSpeed);
	m_npcWdr.changeBehaviour(Behaviour::Wander);

	m_npcSk.setTetxure(&m_alienTxtr);
	m_npcSk.setSpeed(m_npcSpeed);
	m_npcSk.changeBehaviour(Behaviour::Seek);

	m_npcArv.setTetxure(&m_alienTxtr);
	m_npcArv.setSpeed(m_npcSpeed);
	m_npcArv.changeBehaviour(Behaviour::Arrive);

	m_npcFle.setTetxure(&m_alienTxtr);
	m_npcFle.setSpeed(m_npcSpeed);
	m_npcFle.changeBehaviour(Behaviour::Flee);

	m_pi = 2 * acos(0.0);

	do {
		srand(time(0));
		float randX = (rand() % 20) - 10;
		float randY = (rand() % 20) - 10;
		float randX2 = (rand() % 20) - 10;
		float randY2 = (rand() % 20) - 10;
		float randX3 = (rand() % 20) - 10;
		float randY3 = (rand() % 20) - 10;
		float randX4 = (rand() % 20) - 10;
		float randY4 = (rand() % 20) - 10;
		float randX5 = (rand() % 20) - 10;
		float randY5 = (rand() % 20) - 10;

		m_playerVec = sf::Vector2f(randX, randY);
		normaliseVector(m_playerVec);
		m_npcVec = sf::Vector2f(randX2, randY2);
		normaliseVector(m_npcVec);
		m_npcVec2 = sf::Vector2f(randX3, randY3);
		normaliseVector(m_npcVec2);
		m_npcVec3 = sf::Vector2f(randX4, randY4);
		normaliseVector(m_npcVec3);
		m_npcVec4 = sf::Vector2f(randX5, randY5);
		normaliseVector(m_npcVec4);

	} while (m_playerVec == sf::Vector2f(0,0) || m_npcVec == sf::Vector2f(0,0) || m_npcVec2 == sf::Vector2f(0, 0)
				|| m_npcVec3 == sf::Vector2f(0, 0) || m_npcVec4 == sf::Vector2f(0, 0));

	m_player.setMoveVec(m_playerVec);
	m_npcWdr.setMoveVec(m_npcVec);
	m_npcSk.setMoveVec(m_npcVec2);
	m_npcArv.setMoveVec(m_npcVec3);
	m_npcFle.setMoveVec(m_npcVec4);

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
	else if (event.key.code == sf::Keyboard::Down && m_player.getSpeed() > 0.0f )
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
	m_npcWdr.update(m_pi, m_player.getPosition());
	m_npcSk.update(m_pi, m_player.getPosition());
	m_npcArv.update(m_pi, m_player.getPosition());
	m_npcFle.update(m_pi, m_player.getPosition());

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
	m_npcWdr.boundaryCheck(screenSize);
	m_npcSk.boundaryCheck(screenSize);
	m_npcArv.boundaryCheck(screenSize);
	m_npcFle.boundaryCheck(screenSize);
}

sf::Vector2f Game::normaliseVector(sf::Vector2f t_vec)
{
	float vecMag = sqrt((t_vec.x * t_vec.x) + (t_vec.y * t_vec.y));

	sf::Vector2f returnVec = sf::Vector2f(t_vec.x / vecMag, t_vec.y / vecMag);

	return returnVec;
}

void Game::render()
{
	m_window.clear(sf::Color(255,255,255));

	m_player.render(&m_window);
	//m_npcWdr.render(&m_window);
	//m_npcSk.render(&m_window);
	m_npcArv.render(&m_window);
	//m_npcFle.render(&m_window);

	m_window.display();
}


