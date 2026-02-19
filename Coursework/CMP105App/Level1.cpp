#include "Level1.h"


Level1::Level1(sf::RenderWindow& hwnd, Input& in, GameState& gs) :
	BaseLevel(hwnd, in, gs)
{
	int tile_size = 18;
	int num_cols = 20;
	int num_rows = 9;
	int sheet_spacing = 1;
	GameObject tile;
	tile.setSize(sf::Vector2f( tile_size*5, tile_size*5 ));
	tile.setCollisionBox({ { 0,0 },tile.getSize() });
	std::vector<GameObject> tileSet;

	for (int i = 0; i < num_cols * num_rows; i++)
	{
		int row = i / num_cols;
		int col = i % num_cols;
		tile.setTextureRect({
			// position
			{(tile_size + sheet_spacing) * col, (tile_size + sheet_spacing) * row},	
			// size
			{tile_size, tile_size }		
		});
		tile.setCollider(true);
		tileSet.push_back(tile);
	}

	// Add Blank
	tile.setTextureRect({ {0, 0}, {-tile_size, -tile_size} });
	int b = tileSet.size();
	tile.setCollider(false);
	tileSet.push_back(tile);

	std::vector<int> tileMapLocations{
		b,	b,	20,	b,	b,	b,	b,	b,	b,	b,
		b,	21, 104,22,	22,23,	b,	b,	b,	b,
		1,	142,142,142,142,142,3,	b,	81,	83
	};
	sf::Vector2u mapSize = { 10, 3 };

	m_tileMap.setPosition({ 0,200 });
	m_tileMap.loadTexture("gfx/tilemap.png");
	m_tileMap.setTileMap(tileMapLocations, mapSize);
	m_tileMap.setTileSet(tileSet);
	m_tileMap.buildLevel();

	if (!m_tileTexture.loadFromFile("gfx/tilemap.png")) {
		std::cerr << "Could not find Tile Texture." << std::endl;
	}

	m_flag.setTexture(&m_tileTexture);
	m_flag.setTextureRect({ {11 * 19, 5 * 19},{18,18} });
	m_flag.setPosition({ 90 * 9, 344 });
	m_flag.setSize({ 36,36 });
	m_switch.setTexture(&m_tileTexture);
	m_switch.setTextureRect({ {6 * 19,3 * 19}, {18,18} });
	m_switch.setPosition({ 90 * 4, 254 });
	m_switch.setSize({ 36,36 });

	m_player.setInput(&m_input);
}

// handle user input
void Level1::handleInput(float dt)
{
	if (m_input.isLeftMousePressed())
	{
		std::cout << "left mouse pressed" << std::endl;
	}

	m_player.handleInput(dt);
}

// Update game objects
void Level1::update(float dt)
{
	m_player.update(dt);
	
	std::vector<GameObject>& tiles = *m_tileMap.getLevel();
	for (auto t : tiles) {
		//if not a collider skip
		if (!t.isCollider()) continue;

		//if it is a collider and colliding, collide!
		if (Collision::checkBoundingBox(m_player, t)) {
			m_player.collisionResponse(t);
		}
	}
}

// Render Level1
void Level1::render()
{
	beginDraw();
	m_tileMap.render(m_window);

	m_window.draw(m_switch);
	m_window.draw(m_flag);

	m_window.draw(m_player);
	endDraw();
}

