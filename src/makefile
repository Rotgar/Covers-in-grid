cover: main.o graph.o generator.o cover.o
	g++ main.o graph.o generator.o cover.o -o cover

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

graph.o: graph.cpp
	g++ -std=c++11 -c graph.cpp

generator.o: generator.cpp
	g++ -std=c++11 -c generator.cpp

cover.o: cover.cpp
	g++ -std=c++11 -c cover.cpp

clean:
	rm *.o cover
