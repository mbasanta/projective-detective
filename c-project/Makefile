#
# Makefile for projective-detective
#

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	# Do something OSX
else
	
endif

all: clean main projective-detective

main: main.c converter.h converter.c point.h point.c comparisons.h comparisons.c projective-detective.h projective-detective.c
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o main main.c converter.c point.c comparisons.c projective-detective.c /usr/local/Cellar/gdal/1.11.2_1/lib/libgdal.1.dylib -lconfig
	# gcc -ggdb3 -O0 -std=c99 -Wall -Werror -o main main.c converter.c point.c comparisons.c projective-detective.c -lgdal -lconfig -lm

projective-detective: converter.h converter.c point.h point.c comparisons.h comparisons.c projective-detective.h projective-detective.c
	clang -shared -undefined dynamic_lookup -ggdb3 -O0 -std=c99 -Wall -Werror -o projective-detective.so converter.c point.c comparisons.c projective-detective.c /usr/local/Cellar/gdal/1.11.2_1/lib/libgdal.1.dylib -lconfig
	# gcc -shared -undefined -ggdb3 -O0 -std=c99 -Wall -Werror -o projective-detective.so converter.c point.c comparisons.c projective-detective.c -lgdal -lconfig -lm

clean:
	rm -rf *.o *.dSYM a.out main projective-detective
