tron: Cycles.cpp Network.o Game.o Player.o Grid.o
	g++  -o tron Cycles.cpp Network.o Game.o Player.o Grid.o
Network.o: Neural/Network.cpp Neural/Network.h
	g++ -c  Neural/Network.cpp
Game.o: Game/Game.cpp Game/Game.h Grid.o
	g++ -c  Game/Game.cpp
Player.o: Player/Player.cpp Player/Player.h Grid.o
	g++ -c  Player/Player.cpp 
Grid.o: Grid/Grid.cpp Grid/Grid.h
	g++ -c  Grid/Grid.cpp

clean:
	rm test tron *.o
test: t/Tester.cpp Neural/Network.o
	g++ -o test t/Tester.cpp Network.o 

# that's all

