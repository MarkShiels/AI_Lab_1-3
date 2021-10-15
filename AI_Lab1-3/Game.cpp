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
	if (!m_font.loadFromFile("Assets/Highman.ttf"))
	{
		std::cout << "Can't load font " << std::endl;
	}

	m_player.setTetxure(&m_playerTxtr);
	m_player.setSpeed(m_playerSpeed);

	m_npcWdr.setTetxure(&m_alienTxtr);
	m_npcWdr.setSpeed(m_npcSpeed);
	m_npcWdr.changeBehaviour(Behaviour::Wander);
	m_npcWdr.setText("Wander");

	m_npcSk.setTetxure(&m_alienTxtr);
	m_npcSk.setSpeed(m_npcSpeed2);
	m_npcSk.changeBehaviour(Behaviour::Seek);
	m_npcSk.setText("Seek");

	m_npcArv.setTetxure(&m_alienTxtr);
	m_npcArv.setSpeed(m_npcSpeed);
	m_npcArv.changeBehaviour(Behaviour::Arrive);
	m_npcArv.setText("Arrive");

	m_npcFle.setTetxure(&m_alienTxtr);
	m_npcFle.setSpeed(m_npcSpeed2);
	m_npcFle.changeBehaviour(Behaviour::Flee);
	m_npcFle.setText("Flee");

	m_npcPrs.setTetxure(&m_alienTxtr);
	m_npcPrs.setSpeed(m_npcSpeed2);
	m_npcPrs.changeBehaviour(Behaviour::Pursue);
	m_npcPrs.setText("Pursue");

	m_pi = 2 * acos(0.0);

	do {

		srand(time(0));
		float randX = (rand() % 20) - 10;
		float randY = (rand() % 20) - 10;
		float randX2 = (rand() % 20) - 10;
		float randY2 = (rand() % 20) - 10;
		
		m_playerVec = sf::Vector2f(randX, randY);
		normaliseVector(m_playerVec);
		m_npcVec = sf::Vector2f(randX2, randY2);
		normaliseVector(m_npcVec);

	} while (m_playerVec == sf::Vector2f(0, 0) || m_npcVec == sf::Vector2f(0, 0));
			
	m_player.setMoveVec(m_playerVec);
	m_npcWdr.setMoveVec(m_npcVec);

	m_aliens.push_back(m_npcWdr);
	m_aliens.push_back(m_npcSk);
	m_aliens.push_back(m_npcArv);
	m_aliens.push_back(m_npcFle);
	m_aliens.push_back(m_npcPrs);

	for (int i{ 0 }; i < m_aliens.size(); i++)
	{
		m_text2.setFont(m_font);
		m_text2.setFillColor(sf::Color::Black);
		m_text2.setCharacterSize(25);

		m_text2.setString(m_aliens[i].getText());
		m_text2.setPosition(m_aliens[i].getPosition());
		m_text.push_back(m_text2);
	}

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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

	switch (event.key.code)
	{
	case sf::Keyboard::Num1:
		m_aliens[0].toggleDraw();
		break;

	case sf::Keyboard::Num2:
		m_aliens[1].toggleDraw();
		break;

	case sf::Keyboard::Num3:
		m_aliens[2].toggleDraw();
		break;

	case sf::Keyboard::Num4:
		m_aliens[3].toggleDraw();
		break;

	case sf::Keyboard::Num5:
		m_aliens[4].toggleDraw();
		break;

	default:
		break;
	}


}

void Game::update(sf::Time t_tpf)
{
	m_player.update(m_pi);
	sf::Vector2f playerVel = m_player.getMoveVec() * m_player.getSpeed();

	for (int i{ 0 }; i < m_aliens.size(); i++)
	{
		
		m_aliens[i].update(m_pi, m_player.getPosition(), playerVel);
		m_text[i].setPosition(m_aliens[i].getPosition() + sf::Vector2f(-20, 15));
		
	}

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
	for (int i{ 0 }; i < m_aliens.size(); i++)
	{
		
		m_aliens[i].boundaryCheck(screenSize);
		
	}

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

	for (int i{ 0 }; i < m_aliens.size(); i++)
	{
		if (m_aliens[i].getDrawNoDraw())
		{
			m_aliens[i].render(&m_window);
			m_window.draw(m_text[i]);
		}
	}

	m_player.render(&m_window);
	m_window.display();
}


