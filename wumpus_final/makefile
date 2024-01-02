CC=g++ -std=c++11 -g
exe=asm4

run: bats.o event.o game.o gold.o room.o wumpus.o main.o stalactites.o 
	g++ -g bats.o event.o game.o gold.o room.o wumpus.o main.o stalactites.o -o run

bats.o: bats.cpp bats.h
	g++ -g -c bats.cpp

event.o: event.cpp event.h
	g++ -g -c event.cpp

game.o: game.cpp game.h
	g++ -g -c game.cpp

gold.o: gold.cpp gold.h
	g++ -g -c gold.cpp

room.o: room.cpp room.h
	g++ -g -c room.cpp

wumpus.o: wumpus.cpp wumpus.h
	g++ -g -c wumpus.cpp

main.o: main.cpp 
	g++ -g -c main.cpp

stalactites.o: stalactites.cpp stalactites.h
	g++ -g -c stalactites.cpp

clean: 
	rm -f *.out *.o run

