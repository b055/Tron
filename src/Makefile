run: Cycles.cpp Network.o Game.o Player.o Grid.o Evaluate.o Voronoi.o
	g++ -fopenmp -g -o run Cycles.cpp Network.o Game.o Player.o Grid.o Evaluate.o Voronoi.o
Network.o: Neural/Network.cpp Neural/Network.h 
	g++ -fopenmp -g  -c  Neural/Network.cpp
Voronoi.o: Grid/Voronoi.cpp Grid/Voronoi.h
	g++ -fopenmp -g -c Grid/Voronoi.cpp	
Game.o: Game/Game.cpp Game/Game.h Grid.o
	g++ -fopenmp -g -c  Game/Game.cpp
Human.o: Player.o Player/Human.cpp Player/Human.h Voronoi.o
	g++ -g -c Player/Human.cpp
Player.o: Player/Player.cpp Player/Player.h Grid.o Network.o
	g++ -fopenmp -g -c  Player/Player.cpp 
Grid.o: Grid/Grid.cpp Grid/Grid.h Voronoi.o
	g++ -fopenmp -g  -c  Grid/Grid.cpp
Evaluate.o: Evaluate/Evaluate.cpp Evaluate/Evaluate.h Player.o
	g++ -fopenmp -g  -c Evaluate/Evaluate.cpp
Minimax.o: Player.o Player/Minimax.cpp Player/Minimax.h Voronoi.o
	g++ -fopenmp -g -c Player/Minimax.cpp
clean:
	rm test run human tron *.o
test: t/Tester.cpp Neural/Network.o
	g++ -fopenmp -g -o test t/Tester.cpp Network.o 
human: MinimaxVsHuman.cpp Player.o Human.o Game.o Grid.o Voronoi.o Evaluate.o Network.o Minimax.o
	g++ -fopenmp -g -o human MinimaxVsHuman.cpp Player.o Human.o Network.o Game.o Voronoi.o Grid.o Evaluate.o Minimax.o

# that's all

