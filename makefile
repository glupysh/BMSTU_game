library = /opt/homebrew/Cellar/sfml/2.5.1_2

all: game

clean:
	rm game *.o 

game: player.o main.o
	g++ -o game player.o main.o -I $(library)/include -L $(library)/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

main.o: main.cpp player.cpp
	g++ -c main.cpp -I $(library)/include

player.o: player.cpp player.hpp
	g++ -c player.cpp -I $(library)/include