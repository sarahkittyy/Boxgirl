#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <vector>

#include "ResourceManager.hpp"

namespace Graphics
{

/**
 * @brief A basic graphical tilemap. JSON files are generated from
 * Tiled.
 * 
 */
class Tilemap : public sf::Drawable, public sf::Transformable
{
public:
	/**
	 * @brief The tile data type.
	 * 
	 */
	struct Tile
	{
		sf::FloatRect bounds;
		int ID;
	};

	/**
	 * @brief Init the tilemap.
	 * 
	 * @param resource The app resource manager.
	 */
	Tilemap(ResourceManager* resource);

	/**
	 * @brief Load/Init the tilemap from the json file at `path`.
	 * 
	 * @param path The path to the json file.
	 */
	void loadFromFile(const std::string& path);

	/**
	 * @brief Get all tiles on the map with properties matching `props`.
	 * 
	 * @param props The properties to match.
	 * @return std::vector<Tile> A vector of tiles matching `props`.
	 */
	std::vector<Tile> getTiles(nlohmann::json props = {});

	/**
	 * @brief Gets a vector of tile collisions where the tiles have id `id.
	 * 
	 * @param id The ID of the tile type to get. 
	 * @return std::vector<Tile> The tiles on the map.
	 */
	std::vector<Tile> getTiles(int id);

	/**
	 * @brief Get the properties of a tile.
	 * 
	 * @param t The tile ID (0 is empty.)
	 * @return nlohmann::json The json properties.
	 */
	nlohmann::json getTileProperties(int t);

private:
	/**
	 * @brief SFML's draw() override.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	ResourceManager* mResource;   ///< The app resource manager.

	void loadMap();							   ///< Initializes the vertices.
	void loadExtra(const std::string& path);   ///< Load extra tile properties.

	sf::VertexArray mVertices;   ///< The map vertices.
	sf::Texture* mTexture;		 ///< The map texture.

	std::vector<int> mTiles;   ///< The map tiles.

	sf::Vector2i mMapSize;	///< The map size.
	sf::Vector2i mTileSize;   ///< The tile size.

	std::vector<nlohmann::json> mProps;   ///< Extra tile-specific properties.
	nlohmann::json mDefaultProps;		  ///< Default tile properties.
};

}