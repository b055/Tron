run: Cycles.cpp  Game.o Player.o Grid.o Evaluate.o Voronoi.o
	g++ -g -o run Cycles.cpp  Game.o Player.o Grid.o Evaluate.o Voronoi.o

Network.o: Neural/Network.cpp Neural/Network.h 
	g++ -g  -c  Neural/Network.cpp

Voronoi.o: Voronoi.cpp Voronoi.h Chamber.o
	g++ -g -c Voronoi.cpp

Game.o: Game.cpp Game.h Grid.o
	g++ -g -c  Game.cpp

Human.o: Human.cpp Human.h Voronoi.o Player.o 
	g++ -g -c Human.cpp

Player.o: Player.cpp Player.h Grid.o 
	g++ -g -c  Player.cpp

Grid.o: Grid.cpp Grid.h Voronoi.o
	g++ -g  -c  Grid.cpp

Evaluate.o: Evaluate.cpp Evaluate.h Player.o
	g++ -g  -c Evaluate.cpp

Minimax.o: Player.o Minimax.cpp Minimax.h Voronoi.o
	g++ -g -c Minimax.cpp

Chamber.o: Chamber.cpp Chamber.h
	g++ -c Chamber.cpp

clean:
	rm entelect test run human tron chamber *.o *~

human: MinimaxVsHuman.cpp Player.o Human.o Game.o Grid.o Voronoi.o   Minimax.o
	g++ -g -o human MinimaxVsHuman.cpp Player.o Human.o  Game.o Voronoi.o Grid.o Minimax.o Chamber.o

entelect: Player.o Grid.o Voronoi.o Minimax.o Entelect.cpp Chamber.o
	g++ -g -o entelect Entelect.cpp Player.o Grid.o Voronoi.o Minimax.o Chamber.o

chamber:  main.cpp Chamber.o
	g++ -g -o chamber main.cpp Chamber.o
# that's all

