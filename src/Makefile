ron: Cycles.cpp Network.o Game.o Player.o Grid.o Evaluate.o
	g++ -g -o run Cycles.cpp Network.o Game.o Player.o Grid.o Evaluate.o
Network.o: Neural/Network.cpp Neural/Network.h
	g++ -g  -c  Neural/Network.cpp
Game.o: Game/Game.cpp Game/Game.h Grid.o
	g++ -g -c  Game/Game.cpp
Player.o: Player/Player.cpp Player/Player.h Grid.o Network.o
	g++ -g -c  Player/Player.cpp 
Grid.o: Grid/Grid.cpp Grid/Grid.h
	g++ -g  -c  Grid/Grid.cpp
Evaluate.o: Evaluate/Evaluate.cpp Evaluate/Evaluate.h Player.o
	g++ -g  -c Evaluate/Evaluate.cpp
clean:
	rm test run tron *.o
test: t/Tester.cpp Neural/Network.o
	g++ -g -o test t/Tester.cpp Network.o 

# that's all

