#include <chrono>
#include "TetriminoQueue.hpp"


TetriminoQueue::TetriminoQueue() : m_randint(1, Block::NUM_OF_BLOCKS-1) /* NOT block excluded. */
{
	std::random_device rd;
	m_rng = std::mt19937(rd());

	for (int i = 1; i < MAX_QUEUE_LENGTH; ++i)
		//m_queue.push_back(createRandTetrimino());
		m_queue.push_back(std::unique_ptr<Tetrimino>(new Tetrimino(static_cast<Block::Type>(i))));
}

void TetriminoQueue::clear()
{
	m_queue.clear();
}


std::unique_ptr<Tetrimino> TetriminoQueue::pop()
{
	if (m_queue.empty())
		throw std::runtime_error("TetriminoQueue is empty and cannot be dequeued");

	std::unique_ptr<Tetrimino> ret = std::move(m_queue.front());
	/* Remove front and add new piece. */
	m_queue.pop_front();
	m_queue.push_back(createRandTetrimino());

	return ret;
}


/* ALL tetriminos are born here! */
std::unique_ptr<Tetrimino> TetriminoQueue::createRandTetrimino()
{
	Block::Type randBlock = static_cast<Block::Type>(m_randint(m_rng));
	/* TODO: maybe apply random rotation to piece? */
	return std::unique_ptr<Tetrimino>(new Tetrimino(randBlock));
}
