CC := clang++ -std=c++17
CFLAGS := -O2 -pipe -Wall -Wextra
LDFLAGS := -lpthread

.PHONY: clean foodsec

all: belt display

belt: belt.o
	$(CC) -o belt belt.o $(LDFLAGS)

display: display.o
	$(CC) -o display display.o $(LDFLAGS)

belt.o: belt.cpp
	$(CC) $(CFLAGS) -c belt.cpp -o belt.o

display.o: display.cpp
	$(CC) $(CFLAGS) -c display.cpp -o display.o

clean:
	rm -f belt display foodsec *.o *.so *.a *.lib *.fifo

