CC=g++
LINKER:=$(shell pkg-config --cflags --libs /usr/local/Cellar/opencv/4.5.4_2/lib/pkgconfig/opencv4.pc)
CFLAGS=$(LINKER) -std=c++11
DEPS=detect.h linreg.h
OBJ=main.o detect.o linreg.o

%.o: %.cc
	$(CC) -c -o $@ $< $(CFLAGS)

rails: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJ)
