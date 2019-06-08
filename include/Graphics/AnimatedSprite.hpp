#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace Graphics
{

/**
 * @brief An animated sprite class.
 * 
 */
class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
	/**
	 * @brief An animation data structure.
	 * 
	 */
	struct Animation
	{
		std::vector<int> frames;   ///< The frames composing the animation.
		sf::Time speed;			   ///< The animation speed.
	};

	/**
	 * @brief Construct the animated sprite.
	 * 
	 */
	AnimatedSprite();

	///////////////////////////
	//
	// CONFIGURATION
	//
	///////////////////////////

	/// Sets the sprite's texture.
	AnimatedSprite& texture(sf::Texture* tex);
	/// Sets the size of a single animation frame.
	AnimatedSprite& frameSize(sf::Vector2f size);
	/// The size of the sprite when it's drawn.
	AnimatedSprite& renderSize(sf::Vector2f size);
	/// Call after all configuration methods have been set.
	void init();

	///////////////////////////
	//
	// ANIMATION
	//
	///////////////////////////

	/// Add an animation to the sprite.
	void addAnimation(std::string name, Animation anim);
	/// Remove the animation with name `name`.
	void removeAnimation(std::string name);
	/// Get a pointer to the animation with name `name`
	Animation* getAnimation(std::string name);
	/// Set the currently running animation.
	void setAnimation(std::string name);

	//////////////////////////
	/**
	 * @brief Start the animation from the beginning.
	 * 
	 */
	void start();

	/**
	 * @brief Resume the animation
	 * 
	 */
	void resume();

	/**
	 * @brief Pause the animation.
	 * 
	 */
	void pause();

	/**
	 * @brief Stop the animation.
	 * 
	 */
	void stop();

	/**
	 * @brief Update the sprite.
	 * 
	 */
	void update();

	/**
	 * @brief Get the local bounds of the sprite.
	 * 
	 * @return sf::FloatRect The sprite boundaries.
	 */
	sf::FloatRect getLocalBounds();

private:
	/**
	 * @brief SFML's draw() override.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite mSprite;		 ///< The sprite to render.
	sf::Texture* mTexture;   ///< The animation texture map.

	sf::Vector2f mFrameSize;	///< The size of a single sprite frame.
	sf::Vector2f mRenderSize;   ///< The size of the sprite when rendered.

	sf::Clock mAnimationClock;   ///< The animation sprite timer.
	size_t mFrame;				 ///< The current frame.
	Animation* mAnim;			 ///< The current animation.

	bool mRunning;

	/**
	 * @brief Get the FrameRect based on the current frame & the frame size.
	 * 
	 * @return sf::IntRect The current rectangle over the texture to render.
	 */
	sf::IntRect getFrameRect();

	///All animations in this animated sprite.
	std::unordered_map<std::string, Animation> mAnimations;
};

}