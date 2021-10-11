TARGET=game

CC=gcc
RM=rm
CFLAGS=\
  -std=c17 \
  -Wall \
  -Wextra \
  -Wpedantic \
  `sdl2-config --cflags`
LIBS=\
  -lSDL2 \
  -lSDL2_image
OBJS=\
	game.o \
  main.o \
  video.o

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< $(LIBS) -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $@

all: $(TARGET)

clean:
	$(RM) $(OBJS) $(TARGET)
