run: Cycles.cpp Network.o Game.o Player.o Grid.o Evaluate.o Voronoi.o
	g++ -g -o run Cycles.cpp Network.o Game.o Player.o Grid.o Evaluate.o Voronoi.o
Network.o: Neural/Network.cpp Neural/Network.h 
	g++ -g  -c  Neural/Network.cpp
Voronoi.o: Grid/Voronoi.cpp Grid/Voronoi.h Chamber.o
	g++ -g -c Grid/Voronoi.cpp	
Game.o: Game/Game.cpp Game/Game.h Grid.o
	g++ -g -c  Game/Game.cpp
Human.o: Player.o Player/Human.cpp Player/Human.h Voronoi.o
	g++ -g -c Player/Human.cpp
Player.o: Player/Player.cpp Player/Player.h Grid.o Network.o
	g++ -g -c  Player/Player.cpp 
Grid.o: Grid/Grid.cpp Grid/Grid.h Voronoi.o
	g++ -g  -c  Grid/Grid.cpp
Evaluate.o: Evaluate/Evaluate.cpp Evaluate/Evaluate.h Player.o
	g++ -g  -c Evaluate/Evaluate.cpp
Minimax.o: Player.o Player/Minimax.cpp Player/Minimax.h Voronoi.o
	g++ -g -c Player/Minimax.cpp
Chamber.o: Grid/Chamber.cpp Grid/Chamber.h
	g++ -c Grid/Chamber.cpp
clean:
	rm entelect test run human tron *.o
test: t/Tester.cpp Neural/Network.o
	g++ -g -o test t/Tester.cpp Network.o 
human: MinimaxVsHuman.cpp Player.o Human.o Game.o Grid.o Voronoi.o Evaluate.o Network.o Minimax.o
	g++ -g -o human MinimaxVsHuman.cpp Player.o Human.o Network.o Game.o Voronoi.o Grid.o Evaluate.o Minimax.o Chamber.o
entelect: Player.o Grid.o Voronoi.o Minimax.o Entelect.cpp Chamber.o
	g++ -g -o entelect Entelect.cpp Player.o Grid.o Voronoi.o Minimax.o Chamber.o
# that's all

