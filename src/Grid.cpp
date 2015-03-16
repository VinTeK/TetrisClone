#include <iostream>

#include "Grid.hpp"
#include "TetriminoQueue.hpp"


Grid::Grid(TetriminoQueue& queue) : m_dim(sf::Vector2i(GRID_W, GRID_H)), m_queue(&queue)
{
	/* Fill the grid. */
	for (int row = 0; row < m_dim.y; ++row)
		m_grid.push_back(BlockRow(m_dim.x));

	/* Dequeue the first falling piece for the grid. */
	m_falling = m_queue->pop();
}


void Grid::clearLines()
{
	// Scan through the entire grid to find lines need to be cleared
	// This algorithm could be improved
	for (int row = 0; row < GRID_H; ++row) 
	{
		bool bingo = true;

		for (int col = 0; col < GRID_W; ++col) 
		{
			// if this row has any empty block, then check next row
			if (m_grid[row][col] == Block::NIL) 
			{
				bingo = false;
				break;
			}
		}

		if (bingo)
		{
			clearLine(row);
			applyGravity(row);
		}
	}
}

void Grid::clearLine(int target_row)
{
	for (int col = 0; col < GRID_W; ++col)
	{
		m_grid[target_row][col] = Block::NIL;
	}
}

void Grid::applyGravity(int cleared_row)
{
	for (int row = cleared_row - 1; row >= 0; --row)
	{
		for (int col = 0; col < GRID_W; ++col)
		{
			if (m_grid[row][col] != Block::NIL)
			{
				// move down the block by one row
				m_grid[row + 1][col] = m_grid[row][col];
				m_grid[row][col] = Block::NIL;
			}
		}
	}
}


void Grid::moveLeft()
{
	if (!willCollide(sf::Vector2i(-1, 0)))
		m_falling->moveLeft();
}


void Grid::moveRight()
{
	if (!willCollide(sf::Vector2i(1, 0)))
		m_falling->moveRight();
}


void Grid::rotateCounterCW()
{
	if (!willCollide(sf::Vector2i(0, 0), -1))
		m_falling->rotateCounterCW();
	else
	{
		// try wallkicking to the left
		if (!willCollide(sf::Vector2i(-1, 0), -1))
		{
			m_falling->moveLeft();
			m_falling->rotateCounterCW();
			return;
		}
		// try wallkicking to the right
		if (!willCollide(sf::Vector2i(1, 0), -1))
		{
			m_falling->moveRight();
			m_falling->rotateCounterCW();
			return;
		}
	}
}


void Grid::rotateCW()
{
	if (!willCollide(sf::Vector2i(0, 0), 1))
		m_falling->rotateCW();
	else
	{
		// try wallkicking to the left
		if (!willCollide(sf::Vector2i(-1, 0), 1))
		{
			m_falling->moveLeft();
			m_falling->rotateCW();
			return;
		}
		// try wallkicking to the right
		if (!willCollide(sf::Vector2i(1, 0), 1))
		{
			m_falling->moveRight();
			m_falling->rotateCW();
			return;
		}
	}
}


void Grid::softDrop()
{
	if (!willCollide(sf::Vector2i(0, 1)))
		m_falling->dropOne();
	else
		mergeFalling();
}


void Grid::hardDrop()
{
	while (!willCollide(sf::Vector2i(0, 1)))
		m_falling->dropOne();
	mergeFalling();
}


bool Grid::willCollide(const sf::Vector2i& offset, int rotation) const
{
	// create a projection of the falling tetrimino with the offsets applied
	Tetrimino projected = Tetrimino(*m_falling, m_falling->pos() + offset);
	if (rotation > 0)
		projected.rotateCW();
	else if (rotation < 0)
		projected.rotateCounterCW();

	const BlockMatrix& shape = projected.shape();
	const sf::Vector2i& dim = projected.dim();
	const sf::Vector2i& pos = projected.pos();

	for (int row = 0; row < dim.y; ++row)
	{
		for (int col = 0; col < dim.x; ++col)
		{
			// ignore nil blocks
			if (shape[row][col] == Block::NIL)
				continue;

			// floor collision
			if (row + pos.y >= GRID_H)
				return true;

			// left wall collision
			if (col + pos.x < 0)
				return true;

			// right wall collision
			if (col + pos.x >= GRID_W)
				return true;

			// tetrimino collision
			if (m_grid[row + pos.y][col + pos.x] != Block::NIL)
				return true;
		}
	}
	return false;
}


void Grid::mergeFalling()
{
	const BlockMatrix& shape = m_falling->shape();
	const sf::Vector2i& pos = m_falling->pos();

	for (size_t row = 0; row < shape.size(); ++row)
	{
		for (size_t col = 0; col < shape[row].size(); ++col)
		{
			// meld tetrimino blocks into the game grid
			if (shape[row][col] != Block::NIL)
				m_grid[row + pos.y][col + pos.x] = shape[row][col];
		}
	}

	clearLines();

	// destroy falling piece as it is no longer needed
	m_falling.reset();
	// get new piece from queue
	m_falling = m_queue->pop();
}
