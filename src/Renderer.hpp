#pragma once


#include <vector>
#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"

class Grid;


namespace
{
	/* Don't change these! I decided not to allow window resizing because I suck at math.
	TODO: allow window resizing... maybe. */
	const int WINDOW_W = 400;
	const int WINDOW_H = 600;

	/* Length of a side of a single block texture. Measurement in pixels. */
	const int BLOCK_SIZE = 200; 

	/* Scales the view size of the grid. Higher value = larger unit blocks. */
	const float GRID_SCALE = 24.0f;
	/* Space between the grid and the left&bottom edges of the window. Used when
	setting the viewport for the grid. In pixels. */
	const float GRID_MARGIN_SPACE = 16.0f;
}


class Renderer
{
public:
	Renderer(sf::RenderWindow&);

	void draw(const Grid&);
	// void draw(const TetriminoQueue&);

private:
	sf::RenderWindow* m_window;

	TextureManager m_textures;
	FontManager m_fonts;

	std::vector<sf::Sprite> m_blockSprites;

	float m_blockLength;

	sf::View m_gridView;
};
