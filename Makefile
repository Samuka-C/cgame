EXE := .exe # swap to `EXE := ` for linux
CXX := g++ # swap for your prefered c++ compiler

INCLUDE_DIRS := C:/msys64/ucrt64/include C:/glfw-3.4/include include
INCLUDE := $(addprefix -I,$(INCLUDE_DIRS))

LIBS := -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32

main$(EXE): main.o glad.o
	$(CXX) $(INCLUDE) $^ -o $@ $(LIBS)

main.o: src/main.cpp
	$(CXX) $(INCLUDE) -c $< -o $@

glad.o: src/glad.c
	$(CXX) $(INCLUDE) -c $< -o $@