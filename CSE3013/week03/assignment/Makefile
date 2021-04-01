CC = g++
CFLAG = -g -Wno-write-strings

OBJS = main.o Str.o

TARGET = Str

all: $(TARGET)

$(TARGET): $(OBJS)
	     $(CC) $(CFLAG) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CC) $(CFLAG) -c $< -o $@

.PHONY: clean
clean:
	rm $(OBJS) $(TARGET)
