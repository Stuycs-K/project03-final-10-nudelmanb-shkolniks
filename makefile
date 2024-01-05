run: compile
	@./compute

compile: compute.o
	@gcc -o compute compute.o

compute.o: compute.c compute.h
	@gcc -c compute.c

clean:
	@rm -f compute *.o