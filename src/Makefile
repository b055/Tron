run: Cycles.cpp Network.o Game.o Player.o Grid.o Evaluate.o
	g++ -fopenmp -g -o run Cycles.cpp Network.o Game.o Player.o Grid.o Evaluate.o
Network.o: Neural/Network.cpp Neural/Network.h
	g++ -fopenmp -g  -c  Neural/Network.cpp
Game.o: Game/Game.cpp Game/Game.h Grid.o
	g++ -fopenmp -g -c  Game/Game.cpp
Human.o: Player.o Player/Human.cpp Player/Human.h
	g++ -g -c Player/Human.cpp
Player.o: Player/Player.cpp Player/Player.h Grid.o Network.o
	g++ -fopenmp -g -c  Player/Player.cpp 
Grid.o: Grid/Grid.cpp Grid/Grid.h
	g++ -fopenmp -g  -c  Grid/Grid.cpp
Evaluate.o: Evaluate/Evaluate.cpp Evaluate/Evaluate.h Player.o
	g++ -fopenmp -g  -c Evaluate/Evaluate.cpp
clean:
	rm test run human tron *.o
test: t/Tester.cpp Neural/Network.o
	g++ -fopenmp -g -o test t/Tester.cpp Network.o 
human: MachineVsHuman.cpp Player.o Human.o Game.o Grid.o Evaluate.o Network.o
	g++ -fopenmp -g -o human MachineVsHuman.cpp Player.o Human.o Network.o Game.o Grid.o Evaluate.o

# that's all

