#include <algorithm>

#include "Grid.hpp"
#include "Tetrimino.hpp"


/*
Exhaustive definitions of Tetrimino states.
I and O tetriminos are always 4x4; the rest are 3x3.
*/

static BlockMatrix I_TETRIMINO[4] =
{
	{
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL },
		{ Block::I, Block::I, Block::I, Block::I },
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL },
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL }
	},
	{
		{ Block::NIL, Block::NIL, Block::I, Block::NIL },
		{ Block::NIL, Block::NIL, Block::I, Block::NIL },
		{ Block::NIL, Block::NIL, Block::I, Block::NIL },
		{ Block::NIL, Block::NIL, Block::I, Block::NIL }
	},
	{
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL },
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL },
		{ Block::I, Block::I, Block::I, Block::I },
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL }
	},
	{
		{ Block::NIL, Block::I, Block::NIL, Block::NIL },
		{ Block::NIL, Block::I, Block::NIL, Block::NIL },
		{ Block::NIL, Block::I, Block::NIL, Block::NIL },
		{ Block::NIL, Block::I, Block::NIL, Block::NIL }
	}
};

static BlockMatrix J_TETRIMINO[4] =
{
	{
		{ Block::J, Block::NIL, Block::NIL },
		{ Block::J, Block::J, Block::J },
		{ Block::NIL, Block::NIL, Block::NIL }
	},
	{
		{ Block::NIL, Block::J, Block::J },
		{ Block::NIL, Block::J, Block::NIL },
		{ Block::NIL, Block::J, Block::NIL }
	},
	{
		{ Block::NIL, Block::NIL, Block::NIL },
		{ Block::J, Block::J, Block::J },
		{ Block::NIL, Block::NIL, Block::J }
	},
	{
		{ Block::NIL, Block::J, Block::NIL },
		{ Block::NIL, Block::J, Block::NIL },
		{ Block::J, Block::J, Block::NIL }
	}
};

static BlockMatrix L_TETRIMINO[4] =
{
	{
		{ Block::NIL, Block::NIL, Block::L },
		{ Block::L, Block::L, Block::L },
		{ Block::NIL, Block::NIL, Block::NIL }
	},
	{
		{ Block::NIL, Block::L, Block::NIL },
		{ Block::NIL, Block::L, Block::NIL },
		{ Block::NIL, Block::L, Block::L }
	},
	{
		{ Block::NIL, Block::NIL, Block::NIL },
		{ Block::L, Block::L, Block::L },
		{ Block::L, Block::NIL, Block::NIL }
	},
	{
		{ Block::L, Block::L, Block::NIL },
		{ Block::NIL, Block::L, Block::NIL },
		{ Block::NIL, Block::L, Block::NIL }
	}
};

static BlockMatrix O_TETRIMINO[4] =
{
	{
		{ Block::NIL, Block::O, Block::O, Block::NIL},
		{ Block::NIL, Block::O, Block::O, Block::NIL},
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL},
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL}
	},
	{
		{ Block::NIL, Block::O, Block::O, Block::NIL},
		{ Block::NIL, Block::O, Block::O, Block::NIL},
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL},
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL}
	},
	{
		{ Block::NIL, Block::O, Block::O, Block::NIL},
		{ Block::NIL, Block::O, Block::O, Block::NIL},
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL},
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL}
	},
	{
		{ Block::NIL, Block::O, Block::O, Block::NIL},
		{ Block::NIL, Block::O, Block::O, Block::NIL},
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL},
		{ Block::NIL, Block::NIL, Block::NIL, Block::NIL}
	}
};

static BlockMatrix S_TETRIMINO[4] =
{
	{
		{ Block::NIL, Block::S, Block::S },
		{ Block::S, Block::S, Block::NIL },
		{ Block::NIL, Block::NIL, Block::NIL }
	},
	{
		{ Block::NIL, Block::S, Block::NIL },
		{ Block::NIL, Block::S, Block::S },
		{ Block::NIL, Block::NIL, Block::S }
	},
	{
		{ Block::NIL, Block::NIL, Block::NIL },
		{ Block::NIL, Block::S, Block::S },
		{ Block::S, Block::S, Block::NIL }
	},
	{
		{ Block::S, Block::NIL, Block::NIL },
		{ Block::S, Block::S, Block::NIL },
		{ Block::NIL, Block::S, Block::NIL }
	}
};

static BlockMatrix T_TETRIMINO[4] =
{
	{
		{ Block::NIL, Block::T, Block::NIL },
		{ Block::T, Block::T, Block::T },
		{ Block::NIL, Block::NIL, Block::NIL }
	},
	{
		{ Block::NIL, Block::T, Block::NIL },
		{ Block::NIL, Block::T, Block::T },
		{ Block::NIL, Block::T, Block::NIL }
	},
	{
		{ Block::NIL, Block::NIL, Block::NIL },
		{ Block::T, Block::T, Block::T },
		{ Block::NIL, Block::T, Block::NIL }
	},
	{
		{ Block::NIL, Block::T, Block::NIL },
		{ Block::T, Block::T, Block::NIL },
		{ Block::NIL, Block::T, Block::NIL }
	}
};

static BlockMatrix Z_TETRIMINO[4] =
{
	{
		{ Block::Z, Block::Z, Block::NIL },
		{ Block::NIL, Block::Z, Block::Z },
		{ Block::NIL, Block::NIL, Block::NIL }
	},
	{
		{ Block::NIL, Block::NIL, Block::Z },
		{ Block::NIL, Block::Z, Block::Z },
		{ Block::NIL, Block::Z, Block::NIL }
	},
	{
		{ Block::NIL, Block::NIL, Block::NIL },
		{ Block::Z, Block::Z, Block::NIL },
		{ Block::NIL, Block::Z, Block::Z }
	},
	{
		{ Block::NIL, Block::Z, Block::NIL },
		{ Block::Z, Block::Z, Block::NIL },
		{ Block::Z, Block::NIL, Block::NIL }
	}
};


Tetrimino::Tetrimino(Block::Type type) : m_type(type), m_rotstate(0)
{
	/* Spawn center horizontal, one row down from absolute top to just barely peek out. */
	if (type != Block::O)
		m_pos = sf::Vector2i(GRID_W/2 - 2, 1);
	else
		m_pos = sf::Vector2i(GRID_W/2 - 1, 1); // O needs to be slightly shifted
}


Tetrimino::Tetrimino(const Tetrimino& tetrimino, const sf::Vector2i& pos)
	: m_type(tetrimino.m_type)
	, m_rotstate(tetrimino.m_rotstate)
	, m_pos(pos)
{}


const sf::Vector2i Tetrimino::dim() const
{
	if (m_type == Block::I || m_type == Block::O)
		return sf::Vector2i(4, 4);
	return sf::Vector2i(3, 3);
}


const BlockMatrix& Tetrimino::shape() const
{
	switch (m_type)
	{
	case Block::I: return I_TETRIMINO[m_rotstate];
	case Block::J: return J_TETRIMINO[m_rotstate];
	case Block::L: return L_TETRIMINO[m_rotstate];
	case Block::O: return O_TETRIMINO[m_rotstate];
	case Block::S: return S_TETRIMINO[m_rotstate];
	case Block::T: return T_TETRIMINO[m_rotstate];
	case Block::Z: return Z_TETRIMINO[m_rotstate];
	default: throw std::logic_error("cannot rotate tetriminos of this type");
	}
}


// TODO: remove these functions??? Not used anymore...
/*===========================================================================*/

/*
Matrix manipulation helper functions for rotating tetriminos.
*/
BlockMatrix matrix_transpose(const BlockMatrix& mat)
{
	if (mat.size() == 0)
		return mat;

	BlockMatrix ret(mat[0].size());

	/* Operates on [M x N] matrices; Not in-place. */
	for (size_t i = 0; i < mat[0].size(); ++i) {
		BlockRow row(mat.size());
		for (size_t j = 0; j < mat.size(); ++j) {
			row[j] = mat[j][i];
		}
		ret[i] = row;
	}
	return ret;
}


void matrix_reverseRows(BlockMatrix& mat)
{
	for (BlockMatrix::iterator i = mat.begin(); i != mat.end(); ++i)
		std::reverse((*i).begin(), (*i).end());
}
