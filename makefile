run: compile
	@./compute

compile: compute.o spng.o
	@gcc -o compute compute.o spng.o

compute.o: compute.c compute.h
	@gcc -c compute.c

spng.o: spng.c spng.h
	@gcc -c spng.c

clean:
	@rm -f compute *.o