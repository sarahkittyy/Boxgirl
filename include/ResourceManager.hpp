#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

/**
 * @brief Manages expensive resources so only one instance of them
 * is loaded at any given time.
 * 
 */
class ResourceManager
{
public:
	/**
	 * @brief Retrieve the texture at the given path.
	 * 
	 * @param path The path to the texture.
	 * @return sf::Texture* The texture itself.
	 */
	sf::Texture* texture(std::string path);

private:
	/// All app textures, mapped by their path.
	std::unordered_map<std::string, sf::Texture> mTextures;
};