#include "Game.h"

Game::Game() : m_window(sf::VideoMode(1200, 1200, 32), "AI_Lab_1-3", sf::Style::Default)
{
	m_playerVec = sf::Vector2f();
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
	}

}

void Game::update(sf::Time t_tpf)
{
}

void Game::render()
{
	m_window.clear(sf::Color(255,255,255));

	m_player.render(&m_window);
	m_npc.render(&m_window);
	m_window.display();
}
