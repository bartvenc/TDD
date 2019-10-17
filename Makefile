DIST_DIR = dist

OBJECTS = src/main.o src/Game.o src/TextureManager.o src/Map.o src/Vector2D.o
OBJECTS += src/Collision.o src/ECS/ECS.o src/Enemy.o src/Tower.o src/Timer.o src/EnemyManager.o
OBJECTS += src/TowerManager.o
CC = g++

CFLAGS = -g -w -std=c++17

LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image

PHONY: clean make-dist all clean-objects

#This is the target that compiles our executable
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $(LINKER_FLAGS) -c -o $@ $<

main: $(OBJECTS)
	$(CC) $(CFLAGS) $(LINKER_FLAGS) $^ -o dist/$@

clean-dist:
	$(RM) -rf dist

clean-objects:
	$(RM) src/*.o && $(RM) src/ECS/*.o

clean: clean-dist clean-objects

make-dist:
	mkdir dist

all: main

format:
	find ./src -name "*[ch]pp" -exec sh -c 'clang-format -sort-includes=false -style=google {} > .clang-tmp; mv .clang-tmp {}' \;
format8:
	find ./src -name "*[ch]pp" -exec sh -c 'clang-format-8 -sort-includes=false -style=google {} > .clang-tmp; mv .clang-tmp {}' \;

.PHONY: format