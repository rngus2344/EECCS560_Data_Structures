HelloWorld: main.o Executive.o Browser.o
	g++ -std=c++11 -g -Wall main.o Executive.o Browser.o -o HelloWorld

main.o: main.cpp
	g++ -std=c++11 -g -Wall -c main.cpp

Executive.o: Executive.cpp Executive.h
	g++ -std=c++11 -g -Wall -c Executive.cpp

Browser.o: Browser.h Browser.cpp
	g++ -std=c++11 -g -Wall -c Browser.cpp

clean:
	rm *.o HelloWorld



Lab01: main.o executive.o
	g++ -std=c++11 -g -Wall main.o executive.o -o Lab01

main.o: main.cpp executive.h
	g++ -std=c++11 -g -Wall -c main.cpp 

executive.o: executive.h executive.cpp
	g++ -std=c++11 -g -Wall -c executive.cpp 

clean:
	rm *.o Lab01 
