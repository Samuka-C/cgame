EXE := .exe # swap to `EXE := ` for linux
CXX := g++ # swap for your prefered c++ compiler

BIN_DIR := bin
SRC_DIR := src

INCLUDE_DIRS := C:/msys64/ucrt64/include C:/glfw-3.4/include include
INCLUDE := $(addprefix -I,$(INCLUDE_DIRS))

LIBS := -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32

rwildcard = $(foreach d,$(wildcard $1/*),$(call rwildcard,$d,$2)) $(wildcard $1/$2)

CPP_SOURCES := $(call rwildcard,$(SRC_DIR),*.cpp)
C_SOURCES   := $(call rwildcard,$(SRC_DIR),*.c)

CPP_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(CPP_SOURCES))
C_OBJECTS   := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(C_SOURCES))

OBJECTS := $(CPP_OBJECTS) $(C_OBJECTS)

TARGET := $(BIN_DIR)/main$(EXE)

# compile main.cpp to main.exe
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(INCLUDE) $^ -o $@ $(LIBS)

# compile all cpp files to object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(INCLUDE) -c $< -o $@

# compile all c files to object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CXX) $(INCLUDE) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)