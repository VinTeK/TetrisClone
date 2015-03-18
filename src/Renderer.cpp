#include <cassert>

#include "Block.hpp"
#include "Grid.hpp"
#include "Renderer.hpp"


Renderer::Renderer(sf::RenderWindow& window)
	: m_window(&window)
	, m_blockSprites(Block::NUM_OF_BLOCKS)
	, m_gridView(sf::FloatRect(0, 2 * GRID_SCALE, GRID_W * GRID_SCALE, (GRID_H - 2) * GRID_SCALE))
{
	/* Load game assets. */
	m_textures.load("../res/textures/tetrimino_blocks.png", "tetrimino-blocks");
	m_textures.get("tetrimino-blocks").setSmooth(true);

	m_textures.load("../res/textures/tetrimino_i.png", "tetrimino-i");
	m_textures.get("tetrimino-i").setSmooth(true);
	m_textures.load("../res/textures/tetrimino_j.png", "tetrimino-j");
	m_textures.get("tetrimino-j").setSmooth(true);
	m_textures.load("../res/textures/tetrimino_l.png", "tetrimino-l");
	m_textures.get("tetrimino-l").setSmooth(true);
	m_textures.load("../res/textures/tetrimino_o.png", "tetrimino-o");
	m_textures.get("tetrimino-o").setSmooth(true);
	m_textures.load("../res/textures/tetrimino_s.png", "tetrimino-s");
	m_textures.get("tetrimino-s").setSmooth(true);
	m_textures.load("../res/textures/tetrimino_t.png", "tetrimino-t");
	m_textures.get("tetrimino-t").setSmooth(true);
	m_textures.load("../res/textures/tetrimino_z.png", "tetrimino-z");
	m_textures.get("tetrimino-z").setSmooth(true);

	m_fonts.load("../res/fonts/UbuntuMono-R.ttf", "default-font");

	/* Set grid viewport. */
	float vpLeft = GRID_MARGIN_SPACE / WINDOW_W;
	float vpTop = 1.0f - (GRID_MARGIN_SPACE + m_gridView.getSize().y) / WINDOW_H;
	float vpWidth = m_gridView.getSize().x / WINDOW_W;
	float vpHeight = m_gridView.getSize().y / WINDOW_H;
	m_gridView.setViewport(sf::FloatRect(vpLeft, vpTop, vpWidth, vpHeight));

	/* Calculate how much a block sprite will have to be scaled down so that GRID_W x GRID_H
	blocks will fit inside the grid view.  */
	float spriteWidthScale = m_gridView.getSize().x / (BLOCK_SIZE * GRID_W);
	float spriteHeightScale = m_gridView.getSize().y / (BLOCK_SIZE * (GRID_H-2));
	sf::Vector2f blockScaling(spriteWidthScale, spriteHeightScale);
	
	/* Calculate side length of sprite after scaling to use as an offset. */
	m_blockLength = BLOCK_SIZE*blockScaling.x;

	/* Load and scale block sprites. */
	const sf::Texture& blockSpriteSheet = m_textures.get("tetrimino-blocks");
	for (int i = 0; i < Block::NUM_OF_BLOCKS; ++i)
	{
		sf::IntRect spriteSection(BLOCK_SIZE*i, 0, BLOCK_SIZE, BLOCK_SIZE);
		m_blockSprites[i] = sf::Sprite(blockSpriteSheet, spriteSection);
		m_blockSprites[i].scale(blockScaling);
	}
}


void Renderer::draw(const Grid& grid)
{
	/* There MUST BE a falling piece to actually draw... */
	assert(grid.falling() != nullptr);

	/* Set main window view to the grid view. */
	m_window->setView(m_gridView);

	const BlockMatrix& bg = grid.grid();
	size_t matrixSize = bg.size();

	/* Draw background grid. */
	for (size_t row = 0; row < matrixSize; ++row)
	{
		size_t rowSize = bg[row].size();

		for (size_t col = 0; col < rowSize; ++col)
		{
			const Block::Type& block = bg[row][col];
			sf::Sprite blockSprite = m_blockSprites[block];

			/* Move sprite each time so the drawn result is a grid. */
			sf::Transform translation;
			translation.translate(m_blockLength * col, m_blockLength * row);

			m_window->draw(blockSprite, translation);
		}
	}

	const BlockMatrix& falling = grid.falling()->shape();
	const sf::Vector2i& pos = grid.falling()->pos();
	matrixSize = falling.size();

	/* Draw falling tetrimino. */
	for (size_t row = 0; row < matrixSize; ++row)
	{
		size_t rowSize = falling[row].size();

		for (size_t col = 0; col < rowSize; ++col)
		{
			const Block::Type& block = falling[row][col];

			if (block == Block::NIL) // no need to draw the empty NIL blocks
				continue;

			sf::Sprite blockSprite = m_blockSprites[block];

			sf::Transform translation;
			translation.translate(m_blockLength * (col+pos.x), m_blockLength * (row+pos.y));

			m_window->draw(blockSprite, translation);
		}
	}
}
