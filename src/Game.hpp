#pragma once


#include <memory>

#include "Grid.hpp"
#include "Renderer.hpp"
#include "TetriminoQueue.hpp"


class Game
{
public:
	Game();

	void run();

private:
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	float m_turnTime;

	/* GUI elements. */
	Renderer m_renderer;
	TetriminoQueue m_queue;
	Grid m_grid;
};
