#pragma once


#include "Block.hpp"


class Tetrimino
{
public:
	explicit Tetrimino(Block::Type);
	/** Used for creating a copy of a Tetrimino with a different position. */
	Tetrimino(const Tetrimino&, const sf::Vector2i&);

	Block::Type type() const { return m_type; }
	const sf::Vector2i& pos() const { return m_pos; }
	const sf::Vector2i dim() const;
	const BlockMatrix& shape() const;

	void moveLeft() { --m_pos.x; }
	void moveRight() { ++m_pos.x; }
	void dropOne() { ++m_pos.y; }

	void rotateCW() { m_rotstate = (m_rotstate + 1) % 4; }
	void rotateCounterCW() { m_rotstate = (m_rotstate - 1) % 4; if (m_rotstate < 0) m_rotstate += 4;}

private:
	Block::Type m_type;
	int m_rotstate;
	sf::Vector2i m_pos; /* Position on the grid relative to the top-left corner of this shape. */
};
