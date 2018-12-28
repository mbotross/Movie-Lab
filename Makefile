# Makefile for hw4, EECS22 Fall 2017 fall 
# Author: Huan Chen
# Modified by: Mihnea Chirila
# Modification: Ali Nickparsa 11/11/2018
# Date:   11/01/2017
CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall -c -std=c99
LFLAGS = -Wall

DEBUG_OBJS = FileIO_DEBUG.o Image_DEBUG.o 
DEPS = Image.h FileIO.h DIPs.h 

OBJS1=Image.o FileIO.o ImageList.o IterativeFilter.o Movie.o MovieIO.o MovieLab.o

DESIGN = MovieLab
all: MovieLab


MovieLab:  $(OBJS1) libFilter.a
	$(CC) $(LFLAGS) $(OBJS1) -g -lm -L. -lFilter -o MovieLab

libFilter.a: DIPs.o 
	ar rc libFilter.a  DIPs.o
	ranlib libFilter.a


FileIO.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o
DIPs.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o


ImageList.o: ImageList.c ImageList.h Image.h
	$(CC) $(CFLAGS) -g ImageList.c -o ImageList.o
Movie.o: Movie.c Movie.h ImageList.h 
	$(CC) $(CFLAGS) -g Movie.c -o Movie.o
IterativeFilter.o: IterativeFilter.c IterativeFilter.h Image.h Movie.h
	$(CC) $(CFLAGS) -g IterativeFilter.c -o IterativeFilter.o
MovieIO.o: MovieIO.c MovieIO.h Movie.h FileIO.h Image.h
	$(CC) $(CFLAGS) -g MovieIO.c -o MovieIO.o
MovieLab.o: MovieLab.c  MovieIO.h Movie.h IterativeFilter.h ImageList.h $(DEPS)
	$(CC) $(CFLAGS) -g MovieLab.c -o MovieLab.o








FileIO_DEBUG.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) FileIO.c -o FileIO_DEBUG.o
DIPs_DEBUG.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) DIPs.c -o DIPs_DEBUG.o
Image_DEBUG.o: Image.c Image.h
	$(CC) $(CFLAGS) $(DEBUG) Image.c -o Image_DEBUG.o


clean:
	rm -f *.o *.a *.yuv $(DESIGN) `find . -name '*.ppm' ! -name 'HSSOE.ppm'`
	ln -s ~eecs22/public/demo/mouse.yuv 
	ln -s ~eecs22/public/demo/hue.yuv 
	ln -s ~eecs22/public/demo/reverse.yuv

