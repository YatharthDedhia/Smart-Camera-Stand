all: effnet.out

effnet.out: effnet.o
	 gcc -o effnet.out effnet.o

effnet.o: effnet.cc
	 gcc -c effnet.c
     
clean:
	 rm effnet.o effnet.out