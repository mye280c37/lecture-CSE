CC = g++
CFLAGS = -g

OBJS = main.o Array.o RangeArray.o

TARGET = rangearray

all: $(TARGET)

$(TARGET): $(OBJS)
	     $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm *.o $(TARGET)
