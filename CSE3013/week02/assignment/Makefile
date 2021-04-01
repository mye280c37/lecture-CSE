CC= gcc
CFAGS = -g
OBJS = main.o Counting.o Output.o

TARGET = starwars

all: $(TARGET)

$(TARGET): $(OBJS)
	     $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm *.o $(TARGET)
