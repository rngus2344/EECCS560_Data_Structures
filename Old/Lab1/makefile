Lab01: main.o Executive.o
	g++ -std=c++11 -g -Wall main.o Executive.o -o Lab01

main.o: main.cpp
	g++ -std=c++11 -g -Wall -c main.cpp

Executive.o: Executive.cpp Executive.h
	g++ -std=c++11 -g -Wall -c Executive.cpp

clean:
	rm *.o Lab01
