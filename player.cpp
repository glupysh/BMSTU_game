#include "player.hpp"

Player::Player(Texture& image)
{
	sprite.setTexture(image);
	sprite.setTextureRect(IntRect(0, 34, 22, 34));
	sprite.setScale(8, 8);
	sprite.setPosition(552, 380);
	frame = 0;
};

void Player::restart()
{
	sprite.setTextureRect(IntRect(0, 34, 22, 34));
	sprite.setPosition(552, 380);
	frame = 0;
};

void Player::move(int direction, float time)
{
	sprite.move(direction * time * 0.5, 0);
	frame += 0.01 * time;
	if (frame > 8)
		frame -= 8;
	if (direction < 0)
	{
		sprite.setTextureRect(IntRect(22 * int(frame) + 22, 0, -22, 34));
		if (sprite.getPosition().x < - 200)
			sprite.setPosition(1280, 380);
	}
	if (direction > 0)
	{
		sprite.setTextureRect(IntRect(22 * int(frame), 0, 22, 34));
		if (sprite.getPosition().x > 1280)
			sprite.setPosition(-200, 380);
	}
	if (direction == 0)
		sprite.setTextureRect(IntRect(0, 34, 22, 34));
};

bool Player::intersect(FloatRect rect)
{
	if (sprite.getGlobalBounds().intersects(rect))
		return true;
	else
		return false;
};

void Player::draw(RenderWindow& win)
{
	win.draw(sprite);
};

void Player::die()
{
	sprite.setTextureRect(IntRect(22, 34, 22, 34));
};
