run: compile
	@./compute

compile: compute.o
	@gcc -o compute compute.o -lgmp

compute.o: compute.c compute.h
	@gcc -c compute.c

clean:
	@rm -f compute *.o