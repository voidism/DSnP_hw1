CFLAGS = -O3 -Wall
CFLAGS = -g -Wall

p2Run: p2Main.o p2Table.o
	g++ -std=c++11 -o $@ p2Main.o p2Table.o $(CFLAGS)
#	strip $@

p2Main.o: p2Main.cpp p2Table.h
	g++ -std=c++11 -c p2Main.cpp $(CFLAGS)

p2Table.o: p2Table.cpp p2Table.h
	g++ -std=c++11 -c p2Table.cpp $(CFLAGS)

clean:
	rm -f p2Run *.o
