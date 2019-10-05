#Copyright Notice:
#The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2014)
#and may not be redistributed without written permission.

#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp src/Game.cpp src/TextureManager.cpp src/Map.cpp src/Vector2D.cpp
OBJS += src/Collision.cpp src/ECS/ECS.cpp src/Enemy.cpp src/Tower.cpp src/Timer.cpp src/EnemyManager.cpp
OBJS += src/TowerManager.cpp
DEPS = src/ECS/TransformComponent src/ECS/SpriteComponent.hpp src/ECS/ECS.hpp src/ECS/Components.hpp
DEPS += src/Vector2D.hpp src/ECS/KeyboardController.hpp src/ECS/ColliderComponent.hpp src/Collision.hpp
DEPS += src/ECS/TileComponent.hpp src/ECS/Animation.hpp src/Enemy.hpp src/Tower.hpp 
DEPS += src/MatH.hpp src/ECS/CircleComponent.hpp src/ECS/ProjectileComponent.hpp src/Timer.hpp
DEPS += src/EnemyManager.hpp src/TowerManager.hpp
#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -g -w -std=c++17

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image 
#-I/home/jimbeam/Documents/GameEngine/src/Kiwi 
#src/Kiwi/KW_scrollbox_internal.c.o src/Kiwi/KW_scrollbox.c.o src/Kiwi/KW_editbox_internal.c.o src/Kiwi/utf8.c.o src/Kiwi/KW_editbox.c.o src/Kiwi/KW_eventwatcher.c.o src/Kiwi/KW_button.c.o src/Kiwi/KW_label.c.o src/Kiwi/KW_label_internal.c.o src/Kiwi/KW_gui.c.o src/Kiwi/KW_frame.c.o src/Kiwi/KW_frame_internal.c.o src/Kiwi/KW_tilerenderer.c.o src/Kiwi/KW_widget.c.o src/Kiwi/KW_widget_eventhandlers.c.o src/Kiwi/KW_renderdriver.c.o src/Kiwi/KW_renderdriver_sdl2.c.o src/Kiwi/KW_rect.c.o src/Kiwi/KW_toggle.c.o src/Kiwi/KW_checkbox.c.o src/Kiwi/resources.c.o

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = dist/main

PHONY: clean make-dist all

#This is the target that compiles our executable
%.o: %.c $(DEPS)
	$(CC) $(COMPILER_FLAGS) -c -o $@ $<


KiWi_FILES=src/Kiwi/file2c.c src/Kiwi/KW_button.c src/Kiwi/KW_checkbox.c src/Kiwi/KW_editbox.c src/Kiwi/KW_editbox_internal.c src/Kiwi/KW_eventwatcher.c src/Kiwi/KW_frame.c src/Kiwi/KW_frame_internal.c src/Kiwi/KW_gui.c src/Kiwi/KW_label.c src/Kiwi/KW_label_internal.c src/Kiwi/KW_rect.c src/Kiwi/KW_renderdriver.c src/Kiwi/KW_renderdriver_sdl2.c src/Kiwi/KW_scrollbox.c src/Kiwi/KW_scrollbox_internal.c src/Kiwi/KW_tilerenderer.c src/Kiwi/KW_toggle.c src/Kiwi/KW_widget.c src/Kiwi/KW_widget_eventhandlers.c src/Kiwi/utf8.c src/Kiwi/resources.h
kiwi: 
	gcc $(KiWi_FILES) $(LINKER_FLAGS) -o kiwi.o -fvisibility=hidden -pedantic-errors -Wall -Wextra

clean:
	$(RM) -rf dist

make-dist:
	mkdir dist

compile : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

all: compile

format:
	find ./src -name "*[ch]pp" -exec sh -c 'clang-format -sort-includes=false -style=google {} > .clang-tmp; mv .clang-tmp {}' \;
format8:
	find ./src -name "*[ch]pp" -exec sh -c 'clang-format-8 -sort-includes=false -style=google {} > .clang-tmp; mv .clang-tmp {}' \;

.PHONY: format