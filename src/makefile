cover: main.o graph.o generator.o
	g++ main.o graph.o generator.o -o cover

main.o: main.cpp
	g++ -c main.cpp

graph.o: graph.cpp
	g++ -c graph.cpp

generator.o: generator.cpp
	g++ -c generator.cpp

clean:
	rm *.o cover
