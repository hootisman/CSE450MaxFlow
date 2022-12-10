main: NAS.o main.o
	g++ -g -Wall -Wextra -std=c++11 NAS.o main.o -o NAS

main.o: main.cpp NAS.hpp
	g++ -g -c -pthread main.cpp

NAS.o: NAS.cpp NAS.hpp
	g++ -g -c -pthread NAS.cpp

clean:
	rm NAS main.o NAS.o