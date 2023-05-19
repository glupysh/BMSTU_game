#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
using namespace sf; 

class Player
{
private:
	Sprite sprite;
	float frame;
public:
	Player(Texture&);
	void restart();
	void move(int, float);
	bool intersect(FloatRect);
	void draw(RenderWindow&);
	void die();
};

#endif // PLAYER_H
