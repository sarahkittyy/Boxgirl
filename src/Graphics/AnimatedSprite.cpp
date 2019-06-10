#include "Graphics/AnimatedSprite.hpp"

namespace Graphics
{

AnimatedSprite::AnimatedSprite()
	: mFrameSize({16, 16}),
	  mRenderSize({-1, -1}),
	  mFrame(0),
	  mAnim(nullptr),
	  mRunning(false)
{
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

AnimatedSprite& AnimatedSprite::texture(sf::Texture* tex)
{
	//Set the texture
	mTexture = tex;
	return *this;
}

AnimatedSprite& AnimatedSprite::frameSize(sf::Vector2f size)
{
	// Set the frame size.
	mFrameSize = size;
	// Set the render size if it hasn't been set already.
	if (mRenderSize.x == -1 && mRenderSize.y == -1)
	{
		mRenderSize = mFrameSize;
	}
	return *this;
}

AnimatedSprite& AnimatedSprite::renderSize(sf::Vector2f size)
{
	//Set the ideal rendering size.
	mRenderSize = size;
	return *this;
}

void AnimatedSprite::init()
{
	stop();
	mAnimationClock.restart();
	mAnim = nullptr;
	mSprite.setTexture(*mTexture);
	mSprite.setTextureRect(getFrameRect());

	//Scaling the sprite to the ideal size.
	float scaleX = mRenderSize.x / mFrameSize.x;
	float scaleY = mRenderSize.y / mFrameSize.y;

	mSprite.setScale(scaleX, scaleY);
}

void AnimatedSprite::addAnimation(std::string name, Animation anim)
{
	//Insert the animation.
	mAnimations[name] = anim;
}

void AnimatedSprite::removeAnimation(std::string name)
{
	//Remove if exists.
	mAnimations.erase(name);
}

AnimatedSprite::Animation* AnimatedSprite::getAnimation(std::string name)
{
	//Attempt to find the animation.
	auto found = mAnimations.find(name);
	if (found == mAnimations.end())   //Not found
	{
		return nullptr;
	}
	else
	{
		return &found->second;
	}
}

std::string AnimatedSprite::getAnimation()
{
	return mCurrentAnim;
}

void AnimatedSprite::setAnimation(std::string name)
{
	if (getAnimation(name) == mAnim)
	{
		return;
	}
	mFrame		 = 0;
	mAnim		 = getAnimation(name);
	mCurrentAnim = name;
	mSprite.setTextureRect(getFrameRect());
}

void AnimatedSprite::start()
{
	mFrame = 0;
	mAnimationClock.restart();
	mRunning = true;
}

void AnimatedSprite::stop()
{
	mFrame   = 0;
	mRunning = false;
}

void AnimatedSprite::pause()
{
	mRunning = false;
}

void AnimatedSprite::resume()
{
	mRunning = true;
	mAnimationClock.restart();
}

void AnimatedSprite::update()
{
	//Return if not running.
	if (!mRunning || mAnim->speed < sf::seconds(0))
	{
		return;
	}

	//If the animation clock is ready..
	if (mAnimationClock.getElapsedTime() > mAnim->speed)
	{
		mAnimationClock.restart();
		mFrame++;
		if (mFrame >= mAnim->frames.size())
		{
			mFrame = 0;
		}
		mSprite.setTextureRect(getFrameRect());
	}
}

sf::FloatRect AnimatedSprite::getLocalBounds()
{
	return mSprite.getGlobalBounds();
}

sf::IntRect AnimatedSprite::getFrameRect()
{
	// Get the texture map grid x and y size.
	sf::Vector2i grid_size = {(int)mTexture->getSize().x / (int)mFrameSize.x,
							  (int)mTexture->getSize().y / (int)mFrameSize.y};
	//Get the current frame's texture index.
	int ti;
	if (mAnim != nullptr)
	{
		ti = mAnim->frames[mFrame];
	}
	else
	{
		ti = 0;
	}
	//Get the X and Y positions in the texture of the ti.
	int x = (ti % grid_size.x) * mFrameSize.x;
	int y = (ti / grid_size.x) * mFrameSize.y;

	//Return the rect.
	return sf::IntRect(
		x, y,
		mFrameSize.x, mFrameSize.y);
}

}