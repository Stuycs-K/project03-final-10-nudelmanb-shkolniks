compute: compile
	@./compute $(ARGS)

main: compile
	@./main $(ARGS)

compile: compute.o main.o libattopng.o networking.o
	@gcc -o compute compute.o libattopng.o networking.o -lgmp
	@gcc -o main main.o networking.o -lgmp

main.o: main.c networking.h compute.h
	@gcc -c main.c

compute.o: compute.c compute.h networking.h
	@gcc -c compute.c

libattopng.o: libattopng.c libattopng.h
	@gcc -c libattopng.c

networking.o: networking.c networking.h
	@gcc -c networking.c

clean:
	@rm -f compute *.o *.png