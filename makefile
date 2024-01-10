.PHONY: make compile
compile main.out lab.out: client.o server.o
	@gcc -o main.out main.o networking.o -Wall
	@gcc -o lab.out lab.o networking.o -Wall

main: main.out
	@./main.out $(ARGS)

lab: lab.out
	@./lab.out $(ARGS)

main.o: main.c main.h
	@gcc -c main.c -Wall

lab.o: lab.c
	@gcc -c lab.c -Wall

clean:
	@rm *.o 2> /dev/null || true
	@rm *~ 2> /dev/null || true
	@rm main.out lab.out 2> /dev/null || true #for error-handling, can be commented out

rmnfs:
	@rm .nfs*
