# Tower Defence Desktop
> Tower defence desktop game (since we all are tired of mobile TD) project written in C++ with SDL2.

## Current State of the game:
  ECS engine, Animations, Collision Detection, Deterministic Aiming, Generelized Map and Path reading and loading, Enemy and Tower managers are in place and working.

### Changelog:
- Added Tower Manager
- Added Death Animations(Still buggy)

### TODO:
- implement [KiWi GUI](https://github.com/mobius3/KiWi)
- implement wave manager

### Latest update showcase:
![Death Animation](Demo/Death_Animation_1.gif)


# Installation
## Dependencies:
- [SDL2](https://www.libsdl.org/download-2.0.php) 
- [CLANG](https://clang.llvm.org/)

### Ubuntu
```bash
$ sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev clang-format-8
```

### OSX

```bash
$ brew install sdl2 sdl2_image sdl2_ttf clang-format
```

## Compile
> Cmake incomming....

```bash
$ make
```
