#include <iostream>

#include "Game.hpp"


Game::Game()
	: m_window(sf::VideoMode(WINDOW_W, WINDOW_H, 32), "Tetris")
	, m_turnTime(1.0f)
	, m_renderer(m_window)
	, m_grid(m_queue)
{
	m_window.setVerticalSyncEnabled(true);
	//m_window.setFramerateLimit(5);
}


void Game::run()
{
	/* Set clock to start from zero. */
	m_clock.restart();

	/* Game stops running when main RenderWindow is closed. */
	while (m_window.isOpen())
	{
		/* If a turn has ended, process the end of a turn. */
		if (m_clock.getElapsedTime().asSeconds() >= m_turnTime)
		{
			m_grid.softDrop();
			m_clock.restart();
		}

		/* Poll for input events. */
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				sf::Keyboard::Key key = event.key.code;
				switch (key)
				{
				// close window
				case sf::Keyboard::Q:
					m_window.close();
					break;

				// move piece left
				case sf::Keyboard::Left:
					m_grid.moveLeft();
					break;

				// move piece right
				case sf::Keyboard::Right:
					m_grid.moveRight();
					break;

				// soft drop
				case sf::Keyboard::Down:
					m_grid.softDrop();
					m_clock.restart();
					break;

				// hard drop
				case sf::Keyboard::Up:
					m_grid.hardDrop();
					m_clock.restart();
					break;

				// rotate piece CW
				case sf::Keyboard::Z:
					m_grid.rotateCW();
					break;

				// rotate piece CCW
				case sf::Keyboard::X:
					m_grid.rotateCounterCW();
					break;

				// hold piece
				case sf::Keyboard::C:
					// TODO

				default: break;
				}
			}
		}
		/* Draw grid and tetrimino queue. */
		m_window.clear();
		m_renderer.draw(m_grid);
		m_window.display();
	}
}
