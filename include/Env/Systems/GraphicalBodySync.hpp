#pragma once

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"

#include "ECSX/System.hpp"

#include "Env/Components/Components.hpp"

namespace Env::System
{

/**
 * @brief Synchronizes graphical bodies with their Box2D bodies.
 * 
 */
class GraphicalBodySync : public ECSX::System
{
public:
	/**
	 * @brief Moves all transformable objects to their body position.
	 * 
	 */
	void tick();

	/**
	 * @brief The scaling from Box2D -> Graphical coordinates.
	 * 
	 * @return const float The scale from box2d -> graphical.
	 */
	static const float scale();

	/**
	 * @brief The scaling from Graphical -> Box2D coordinates.
	 * 
	 * @return const float Scaling factor from graphical -> box2d.
	 */
	static const float invscale();

	/**
	 * @brief Orients an SFML object such that it's origin is in it's center.
	 * 
	 * @tparam T Has setOrigin() and .getLocalBounds().
	 * @param object The SFML object to orient.
	 */
	template <typename T>
	static void orientCenter(T* object)
	{
		//Orient the object on it's center.
		object->setOrigin(object->getLocalBounds().width / 2.f,
						  object->getLocalBounds().height / 2.f);
	}

	/**
	 * @brief Get the half size of a SFML object.
	 * 
	 * @tparam T Has .getLocalBounds()
	 * @param object The object.
	 * @return sf::Vector2f The half size of that object.
	 */
	template <typename T>
	static sf::Vector2f halfSize(T& object)
	{
		return sf::Vector2f(
			object.getLocalBounds().width / 2.f,
			object.getLocalBounds().height / 2.f);
	}

	/**
	 * @brief Get the half size of a float rect.
	 * 
	 * @param object The rect.
	 * @return sf::Vector2f The rect's half size.
	 */
	template <>
	sf::Vector2f halfSize(sf::FloatRect& object)
	{
		return sf::Vector2f(
			object.width / 2.f,
			object.height / 2.f);
	}

	/**
	 * @brief Convert an sf::Vector2f to a b2Vec2
	 * 
	 * @param in The input vector.
	 * @param scaleCoords Whether or not to scale the vector as well.
	 * @return b2Vec2 The converted vector.
	 */
	static b2Vec2 fromVector(sf::Vector2f in, bool scaleCoords = true);

	/**
	 * @brief Convert a b2Vec2 to an sf::Vector2f
	 * 
	 * @param in The input vector.
	 * @param scaleCoords Whether or not to scale the vector coords as well.
	 * @return sf::Vector2f The output vector.
	 */
	static sf::Vector2f toVector(b2Vec2 in, bool scaleCoords = true);

private:
	/// Transform from Box2D to graphical.
	static constexpr float SCALE = 20.f;
};

}