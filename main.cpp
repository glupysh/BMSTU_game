#include <SFML/Audio.hpp>
#include <ctime>
#include <sstream>
#include <iostream>
#include "player.hpp"

using namespace std;

string IntToStr(int number)
{
    ostringstream TextString;
    TextString << number;
    return TextString.str();
}

int main()
{
	RenderWindow win(sf::VideoMode(1280, 720), "BMSTU");
	srand(time(NULL));
	bool play = false;
	bool pause = false;
	bool die = false;
	bool mus = false;
	int life = 3;
	int count = 0;
	Clock clock;
	
	Font GameFont;
	GameFont.loadFromFile("font/videotype.otf");

	Text text_start;
	text_start.setFont(GameFont);
	text_start.setFillColor(Color::Black);
	text_start.setString("Space To Start"); 
	text_start.setCharacterSize(70);
	text_start.setPosition(350, 250);

	Text text_pause;
	text_pause.setFont(GameFont);
	text_pause.setFillColor(Color::Black);
	text_pause.setString("Pause"); 
	text_pause.setCharacterSize(50);
	text_pause.setPosition(500, 200);

	Text text_end;
	text_end.setFont(GameFont);
	text_end.setFillColor(Color::Black);
	text_end.setString("Game Over"); 
	text_end.setCharacterSize(50);
	text_end.setPosition(500, 200);

	Text text_score;
	text_score.setFont(GameFont);
	text_score.setFillColor(Color::Black);
	text_score.setString("Score:"); 
	text_score.setCharacterSize(60);
	text_score.setPosition(30, 10);
	
	Text text_count;
	text_count.setFont(GameFont);
	text_count.setFillColor(Color::Black);
	text_count.setString(IntToStr(count));
	text_count.setCharacterSize(60);
	text_count.setPosition(350, 10);

	Text text_life;
	text_life.setFont(GameFont);
	text_life.setFillColor(Color::Black);
	text_life.setString("Life:"); 
	text_life.setCharacterSize(60);
	text_life.setPosition(870, 10);

	Texture s;
	s.loadFromFile("image/sky.png");
	Sprite sky(s);
	sky.setScale(8, 8);

	Texture u;
	u.loadFromFile("image/university.png");
	Sprite university(u);
	university.setScale(8, 8);
	university.setPosition(0, -15);

	Texture g;
	g.loadFromFile("image/ground.png");
	Sprite ground(g);
	ground.setScale(8, 8);
	ground.setPosition(0, 625);

	Texture h;
	h.loadFromFile("image/heart.png");
	Sprite heart(h);
	heart.setTextureRect(IntRect(0, 0, 14 * life, 11));
	heart.setScale(5, 5);
	heart.setPosition(1050, 20);

	Texture c;
	c.loadFromFile("image/cloud.png");
	Sprite cloud[2];
	for (int i = 0; i < 2; i++)
	{
		cloud[i].setTexture(c);
		cloud[i].setScale(8, 8);
		cloud[i].setPosition(1280 * i - 1280, 0);
	}

	Texture p;
	p.loadFromFile("image/player.png");
	Player player(p);

	Texture b;
	b.loadFromFile("image/book.png");
	Sprite book[5];
	for (int i = 0; i < 5; i++)
	{
		book[i].setTexture(b);
		book[i].setScale(4, 4);
		book[i].setPosition(10 + 225 * i, -80 - 10 * (rand() % 80));
	}

	Music music;
	music.openFromFile("audio/music.wav");
	music.setLoop(true);

	SoundBuffer e;
	e.loadFromFile("audio/end.wav");
	Sound end;
	end.setBuffer(e);

	SoundBuffer coin;
	coin.loadFromFile("audio/coin.wav");
	Sound collect;
	collect.setBuffer(coin);

	while (win.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
				win.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
					win.close();
				if (event.key.code == Keyboard::M)
				{
					mus = !mus;
					if (mus) 
						music.play();
					else
						music.stop();
				}
				if (event.key.code == Keyboard::Space && !play)
				{
					play = true;
					if (die)
					{
						die = false;
						life = 3;
						count = 0;
						text_count.setString(IntToStr(count));
						heart.setTextureRect(IntRect(0, 0, 14 * life, 11));
						player.restart();
						for (int i = 0; i < 5; i++)
							book[i].setPosition(10 + 225 * i, -80 - 10 * (rand() % 80));
					}
				}
				else if (event.key.code == Keyboard::P && play && !die)
					pause = !pause;
			}
		}
		if (play && !pause)
		{	
			if (Keyboard::isKeyPressed(Keyboard::Left))
				player.move(-1, time);
			else if (Keyboard::isKeyPressed(Keyboard::Right))
				player.move(1, time);
			else
				player.move(0, time);
			for (int i = 0; i < 2; i++)
			{
				cloud[i].move(0.1 * time, 0);
				if (cloud[i].getPosition().x > 1280)
					cloud[i].setPosition(-1280, 0);
			}
			for (int i = 0; i < 5; i++)
			{
				book[i].move(0, time / 7);
				if (book[i].getPosition().y > 630)
				{
					life--;
					heart.setTextureRect(IntRect(0, 0, 14 * life, 11));
					book[i].setPosition(10 + 225 * i, -80 - 10 * (rand() % 80));
				}
				if (player.intersect(book[i].getGlobalBounds()))
				{
					collect.play();
					text_count.setString(IntToStr(++count));
					book[i].setPosition(10 + 225 * i, -80 - 10 * (rand() % 80));
				}
			}
			if (life == 0)
			{
				end.play();
				player.die();
				play = false;
				die = true;
			}
		}
		win.clear();
		win.draw(sky);
		for (int i = 0; i < 2; i++)
			win.draw(cloud[i]);
		win.draw(university);
		for (int i = 0; i < 5; i++)
			win.draw(book[i]);
		win.draw(ground);
		player.draw(win);
		win.draw(text_score);
		win.draw(text_count);
		win.draw(text_life);
		win.draw(heart);	
		if (!play)
			win.draw(text_start);
		if (die)
			win.draw(text_end);
		if (pause)
			win.draw(text_pause);
		win.display();
	}
	return 0;
}