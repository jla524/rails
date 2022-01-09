CC=g++
LINKER:=$(shell pkg-config --cflags --libs /usr/local/Cellar/opencv/4.5.4_2/lib/pkgconfig/opencv4.pc)
CFLAGS=$(LINKER) -std=c++11
OBJ=display.o

%.o: %.cc
	$(CC) -c -o $@ $< $(CFLAGS)

display: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJ)
