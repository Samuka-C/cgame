EXE := .exe # swap to `EXE := ` for linux
CXX := g++ # swap for your prefered c++ compiler

BIN_DIR := bin

INCLUDE_DIRS := C:/msys64/ucrt64/include C:/glfw-3.4/include include
INCLUDE := $(addprefix -I,$(INCLUDE_DIRS))

LIBS := -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32
OBJECT_LIST := $(BIN_DIR)/window.o \
			   $(BIN_DIR)/logger.o \
			   $(BIN_DIR)/glad.o \
			   $(BIN_DIR)/color.o

$(BIN_DIR)/main$(EXE): $(BIN_DIR)/main.o $(OBJECT_LIST) | $(BIN_DIR)
	$(CXX) $(INCLUDE) $^ -o $@ $(LIBS)

$(BIN_DIR)/main.o: src/main.cpp | $(BIN_DIR)
	$(CXX) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/logger.o: src/Logger/logger.cpp | $(BIN_DIR)
	$(CXX) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/window.o: src/UI/window.cpp | $(BIN_DIR)
	$(CXX) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/color.o: src/Util/Color/color.cpp | $(BIN_DIR)
	$(CXX) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/glad.o: src/glad.c | $(BIN_DIR)
	$(CXX) $(INCLUDE) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)