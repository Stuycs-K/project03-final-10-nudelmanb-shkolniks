run: compile
	@./compute

compile: compute.o libattopng.o networking.o
	@gcc -o compute compute.o libattopng.o

compute.o: compute.c compute.h networking.h
	@gcc -c compute.c

libattopng.o: libattopng.c libattopng.h
	@gcc -c libattopng.c

networking.o: networking.c networking.h
	@gcc -c networking.c

clean:
	@rm -f compute *.o *.png