all: Main.o Edge.o Vertex.o
		g++ -std=c++98 -g -Wall Main.o Edge.o Vertex.o -o dijkstra

Edge.o: Edge.h Edge.cpp
		g++ -std=c++98 -g -Wall -c Edge.cpp

Vertex.o: Vertex.h Vertex.cpp
		g++ -std=c++98 -g -Wall -c Vertex.cpp

Main.o: Main.cpp
		g++ -std=c++98 -g -Wall -c Main.cpp

clean:
		rm -f *.o dijkstra