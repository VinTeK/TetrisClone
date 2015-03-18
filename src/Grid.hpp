#pragma once


#include <memory>
#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "Tetrimino.hpp"

class TetriminoQueue;


namespace
{
	/* Default Tetris grid dims as the traditional 10 wide x 20 tall. */
	const int GRID_W = 10;
	const int GRID_H = 20;
}


class Grid
{
public:
	/** A grid must be connected with a queue to receive new falling pieces. */
	Grid(TetriminoQueue&);

	const BlockMatrix& grid() const { return m_grid; }
	const std::unique_ptr<Tetrimino>& falling() const { return m_falling; }

	/** Clears lines in the grid and then applies gravity. */
	void clearLines();

	/** Applies gravity to all blocks above the cleared row (moving down all blocks by 1) */
	void applyGravity(int cleared_row);

	/* Falling piece manipulation functions. */
	void moveLeft();
	void moveRight();
	void rotateCW();
	void rotateCounterCW();
	void softDrop();
	void hardDrop();

	/** Falling piece collision detection. 1 -> clockwise, -1 -> counter-clockwise */
	bool willCollide(const sf::Vector2i& offset, int rotation = 0) const;

private:
	/** Empty the line blocks. */
	void clearLine(int target_row);
	void mergeFalling();

private:
	sf::Vector2i m_dim; // (x = width, y = height)
	BlockMatrix m_grid;
	TetriminoQueue* m_queue;

	std::unique_ptr<Tetrimino> m_falling;
};
