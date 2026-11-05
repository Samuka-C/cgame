# CGAME

![Static Badge](https://img.shields.io/badge/language-C%2B%2B-orange)

A very simple game engine designed for:

- 2D games
- singleplayer games

Made by: Samuka-C

## How to use

To use this engine, you need to have it as a submodule of you game repository.

with: `git submodule add git@github.com:Samuka-C/cgame.git cgame`

### Dependencies

glfw-3.4 - https://www.glfw.org/download
*(the version used is the 3.4. I am not sure if more recent versions will work)*

a c compiler *(probably any will do)*

### Adjust CGame MakeFile

update INCLUDE_DIRS with the include path of glfw and the c compiler

### Adjust your MakeFile

add this *(or something like this)* to your makefile

```MakeFile
CGAME_DIR := cgame
CGAME_LIB := $(CGAME_DIR)/bin/libcgame.a

.PHONY: $(CGAME_LIB)

$(CGAME_LIB):
	$(MAKE) -C $(CGAME_DIR)
```

this will make so everytime you compile your game, the make will attempt to make the `libcgame.a` if the files are not changed. nothing will happen.

Then use `$(CGAME_LIB)` when compiling your executable.

and make sure to add
`-Icgame/include` when compiling files that include files from cgame.

### Example repository
to see a example of a simple game that uses cgame and how they handle the makefile, check https://github.com/Samuka-C/pong-cgame

