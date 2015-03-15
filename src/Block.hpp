/**
Some definitions:
- tetrimino: a complete shape composed of four connected blocks.
- block: a single unit element of the grid; a single unit of a larger tetrimino.
*/
#pragma once


#include <vector>


/* Definitions for a single block. */
namespace Block
{
	/* Sprite sheet MUST be in this order! */
	enum Type { NIL, I, J, L, O, S, T, Z, NUM_OF_BLOCKS };
}


/* A single row or line in the grid. */
typedef std::vector<Block::Type> BlockRow;
/* A two-dimensional matrix for representing the game world. */
typedef std::vector<BlockRow> BlockMatrix;
