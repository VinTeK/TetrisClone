/**
The game's queue that contains upcoming tetriminos and schedules new ones to come.
*/
#pragma once


#include <deque>
#include <memory>
#include <random>
#include <SFML/Graphics.hpp>
#include "Tetrimino.hpp"


namespace
{
	const int MAX_QUEUE_LENGTH = 8;
}


class TetriminoQueue
{
public:
	TetriminoQueue();

	void clear();
	std::unique_ptr<Tetrimino> pop();

private:
	std::unique_ptr<Tetrimino> createRandTetrimino();

private:
	std::mt19937 m_rng;
	std::uniform_int_distribution<int> m_randint;

	std::deque<std::unique_ptr<Tetrimino> > m_queue;
};
