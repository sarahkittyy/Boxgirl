#include "Graphics/Tilemap.hpp"

namespace Graphics
{

Tilemap::Tilemap(ResourceManager* resource)
	: mResource(resource)
{
	mVertices.setPrimitiveType(sf::Quads);
}

void Tilemap::loadFromFile(const std::string& path)
{
	using nlohmann::json;

	//Open the file
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Could not open file " + path + "\n");
	}
	json data;   // Read the data.
	file >> data;
	file.close();   //Close the file

	//Get the map width & height.
	mMapSize.x = data.at("width");
	mMapSize.y = data.at("height");
	//Tile width & height
	mTileSize.x = data.at("tilewidth");
	mTileSize.y = data.at("tileheight");
	//Tile data.
	mTiles = data.at("layers")[0].at("data").get<std::vector<int>>();
	//Texture path.
	std::string str = "resource/maps/" + data.at("tilesets")[0].at("image").get<std::string>();
	//Load the texture.
	mTexture = mResource->texture(str);

	loadMap();		   // Load the map from mTiles
	loadExtra(path);   // Load extra map data.
}

void Tilemap::loadMap()
{
	mVertices.clear();

	//Texture grid size.
	sf::Vector2i texGridSize(mTexture->getSize().x / mTileSize.x,
							 mTexture->getSize().y / mTileSize.y);

	//Iterate over all tiles in mTiles.
	int index = -1;
	for (auto& tileID : mTiles)
	{
		index++;
		int id = tileID;
		//0 tiles are empty, ignore them.
		if (id-- == 0)
		{
			continue;
		}

		//Get the texture x and y position
		int x = id % texGridSize.x;
		int y = id / texGridSize.x;
		x *= mTileSize.x;
		y *= mTileSize.y;

		//Get the map x and y position.
		int mx = index % mMapSize.x;
		int my = index / mMapSize.x;
		mx *= mTileSize.x;
		my *= mTileSize.y;

		//Create the four vertices
		mVertices.append(sf::Vertex(
			sf::Vector2f(mx, my),
			sf::Vector2f(x, y)));
		mVertices.append(sf::Vertex(
			sf::Vector2f(mx + mTileSize.x, my),
			sf::Vector2f(x + mTileSize.x, y)));
		mVertices.append(sf::Vertex(
			sf::Vector2f(mx + mTileSize.x, my + mTileSize.y),
			sf::Vector2f(x + mTileSize.x, y + mTileSize.y)));
		mVertices.append(sf::Vertex(
			sf::Vector2f(mx, my + mTileSize.y),
			sf::Vector2f(x, y + mTileSize.y)));
	}
}

void Tilemap::loadExtra(const std::string& path)
{
	using nlohmann::json;
	namespace fs = std::filesystem;

	fs::path p(path);   // Load the path.
	fs::path props_file(p.parent_path().string() + "/" + p.stem().string() + ".props.json");
	//Read the data.
	std::ifstream file(props_file);
	json data;
	file >> data;
	file.close();   // Close the file.

	//Get the default props.
	mDefaultProps = data.at("default");
	//For every tile-specific prop...
	for (auto& obj : data.at("props"))
	{
		//Push it back.
		mProps.push_back(obj);
	}
}

std::vector<Tilemap::Tile> Tilemap::getTiles(nlohmann::json props)
{
	std::vector<Tile> tiles;

	//For every tile...
	for (int i = 0; i < mTiles.size(); ++i)
	{
		//Get the tile ID.
		int tileID = mTiles[i];
		//Get the tile properties.
		auto tileProps = getTileProperties(tileID);

		//Iterate over all necessary props.
		bool isValid = true;
		for (auto& [key, value] : props.items())
		{
			//Skip tiles that don't match 'props'.
			if (tileProps.find(key) == tileProps.end() || tileProps[key] != value)
			{
				isValid = false;
				break;
			}
		}
		if (!isValid)
		{
			continue;
		}
		//Tile position.
		int x = i % mMapSize.x;
		int y = i / mMapSize.x;
		x *= mTileSize.x;
		y *= mTileSize.y;

		//Append the tile.
		tiles.push_back({.bounds = sf::FloatRect(
							 x, y,
							 mTileSize.x, mTileSize.y),
						 .ID = tileID});
	}

	return tiles;
}

std::vector<Tilemap::Tile> Tilemap::getTiles(int id)
{
	std::vector<Tile> tiles;

	//For every tile...
	for (int i = 0; i < mTiles.size(); ++i)
	{
		//Get the tile ID.
		int tileID = mTiles[i];
		if (id == tileID)   //If it matches, append it.
		{
			//Tile position.
			int x = i % mMapSize.x;
			int y = i / mMapSize.x;
			x *= mTileSize.x;
			y *= mTileSize.y;

			//Append the tile.
			tiles.push_back({.bounds = sf::FloatRect(
								 x, y,
								 mTileSize.x, mTileSize.y),
							 .ID = tileID});
		}
	}
	//Return constructed tiles.
	return tiles;
}

nlohmann::json Tilemap::getTileProperties(int t)
{
	using nlohmann::json;

	// If the data doesn't exist, return default.
	if (t > mProps.size())
	{
		return mDefaultProps;
	}
	else   // Otherwise...
	{
		// Get the data.
		json data = mProps[t];

		//Iterate over all key-value pairs in mDefaultProps.
		for (auto& [key, value] : mDefaultProps.items())
		{
			//If data doesn't have `key`, append the default value.
			if (data.find(key) == data.end())
			{
				data[key] = value;
			}
		}

		//Return the data.
		return data;
	}
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = mTexture;
	target.draw(mVertices, states);
}

}