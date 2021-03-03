CC = gcc
CFLAGS = -g -Wall -Wextra
LDFLAGS = -lm
OBJFILES = main.o pile.o file.o
TARGET = prog

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)

