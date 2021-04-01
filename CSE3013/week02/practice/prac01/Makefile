animal_exe : dog.o blackcow.o turtle.o main.o
	gcc -o animal.exe dog.o blackcow.o turtle.o main.o

dog.o : dog.c
	 gcc -c -o dog.o dog.c

blackcow.o : blackcow.c
	gcc -c -o blackcow.o blackcow.c

turtle.o : turtle.c
	gcc -c -o turtle.o turtle.c

main.o : main.c
	gcc -c -o main.o main.c

.PHONY: clean
clean:
	rm *.o animal.exe
