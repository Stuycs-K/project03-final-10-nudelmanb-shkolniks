run: compile
	@./compute

compile: compute.o libattopng.o
	@gcc -o compute compute.o libattopng.o

compute.o: compute.c compute.h
	@gcc -c compute.c

libattopng.o: libattopng.c libattopng.h
	@gcc -c libattopng.c

clean:
	@rm -f compute *.o *.png