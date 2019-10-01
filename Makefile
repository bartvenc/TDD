#Copyright Notice:
#The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2014)
#and may not be redistributed without written permission.

#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp src/Game.cpp src/TextureManager.cpp src/Map.cpp src/Vector2D.cpp
OBJS += src/Collision.cpp src/ECS/ECS.cpp src/Enemy.cpp src/Tower.cpp src/Timer.cpp src/EnemyManager.cpp
DEPS = src/ECS/TransformComponent src/ECS/SpriteComponent.hpp src/ECS/ECS.hpp src/ECS/Components.hpp
DEPS += src/Vector2D.hpp src/ECS/KeyboardController.hpp src/ECS/ColliderComponent.hpp src/Collision.hpp
DEPS += src/ECS/TileComponent.hpp src/ECS/Animation.hpp src/Enemy.hpp src/Tower.hpp 
DEPS += src/MatH.hpp src/ECS/CircleComponent.hpp src/ECS/ProjectileComponent.hpp src/Timer.hpp
DEPS += src/EnemyManager.hpp
#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -g -w -std=c++17

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = dist/main

PHONY: clean make-dist all

#This is the target that compiles our executable
%.o: %.c $(DEPS)
	$(CC) $(COMPILER_FLAGS) -c -o $@ $<

clean:
	$(RM) -rf dist

make-dist:
	mkdir dist

compile : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

all: compile
