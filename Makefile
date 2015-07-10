#
# Makefile for pset 1
#

all: clean main converter

main: main.c converter.h converter.c
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o main main.c converter.c /usr/local/Cellar/gdal/1.11.2_1/lib/libgdal.1.dylib -lconfig

converter: converter.c
	clang -shared -undefined dynamic_lookup -ggdb3 -O0 -std=c99 -Wall -Werror -o converter.so converter.c /usr/local/Cellar/gdal/1.11.2_1/lib/libgdal.1.dylib

clean:
	rm -rf *.o *.dSYM a.out main converter
