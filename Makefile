CC=g++
LINKER:=$(shell pkg-config --cflags --libs /usr/local/Cellar/opencv/4.5.4_3/lib/pkgconfig/opencv4.pc)
CFLAGS=$(LINKER) -std=c++11
DEPS=src/detect.h src/process.h src/linreg.h
OBJ=src/main.o src/detect.o src/process.o src/linreg.o

%.o: %.cc
	$(CC) -c -o $@ $< $(CFLAGS)

rails: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJ)
