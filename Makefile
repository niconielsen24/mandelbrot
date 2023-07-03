CC =gcc
FLAGS =-lGL -lGLEW -lglfw -Wall -Wextra
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
TARGET = mandelbrot

all:$(TARGET)

$(OBJS):$(SRCS)
	$(CC) $(SRCS) $(FLAGS) -c -g

$(TARGET):$(OBJS)
	$(CC) $(OBJS) $(FLAGS) -g -o $@

clean:
	rm *.o $(TARGET)
	
run:
	./$(TARGET)
