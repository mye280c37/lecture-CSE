cc=gcc
cflags = -W -g
target = main

objects = main.o String_Manipulation.o Output.o

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

main.o String_Manipulation.o Output.o : Header.h

.PHONY : clean
clean :
	rm $(target) $(objects)
