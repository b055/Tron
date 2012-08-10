tron: Cycles.cpp Network.o Game.o Player.o Grid.o Evaluate.o
	g++ -fopenmp -o tron Cycles.cpp Network.o Game.o Player.o Grid.o Evaluate.o
Network.o: Neural/Network.cpp Neural/Network.h
	g++ -fopenmp -c  Neural/Network.cpp
Game.o: Game/Game.cpp Game/Game.h Grid.o
	g++ -fopenmp -c  Game/Game.cpp
Player.o: Player/Player.cpp Player/Player.h Grid.o Network.o
	g++ -fopenmp -c  Player/Player.cpp 
Grid.o: Grid/Grid.cpp Grid/Grid.h
	g++ -fopenmp -c  Grid/Grid.cpp
Evaluate.o: Evaluate/Evaluate.cpp Evaluate/Evaluate.h Player.o
	g++ -fopenmp -c Evaluate/Evaluate.cpp
clean:
	rm test tron *.o
test: t/Tester.cpp Neural/Network.o
	g++ -o test t/Tester.cpp Network.o 

# that's all

