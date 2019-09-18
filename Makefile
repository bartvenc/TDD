#Copyright Notice:
#The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2014)
#and may not be redistributed without written permission.

#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp src/Game.cpp src/TextureManager.cpp  src/GameObject.cpp  src/Map.cpp src/Vector2D.cpp
OBJS += src/Collision.cpp src/ECS/ECS.cpp
DEPS = src/ECS/TransformComponent src/ECS/SpriteComponent.hpp src/ECS/ECS.hpp src/ECS/Components.hpp
DEPS += src/Vector2D.hpp src/ECS/KeyboardController.hpp src/ECS/ColliderComponent.hpp src/Collision.hpp
DEPS += src/ECS/TileComponent.hpp src/ECS/Animation.hpp
#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -g -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
%.o: %.c $(DEPS)
	$(CC) $(COMPILER_FLAGS) -c -o $@ $<
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)