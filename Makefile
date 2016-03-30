ifeq ($(OS),Windows_NT)
CC = gcc
CFLAGS = -Wall
LDFLAGS  = -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32 -lm

APP_BIN = Hovercraft

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = -I include
BIN_PATH = bin
LIB_PATH = lib
MKDIR_P = mkdir


SRC_FILES = $(wildcard src/*.c) $(wildcard src/*/*.c)
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))

all: $(APP_BIN)
		@echo $(SRC_FILES)

$(APP_BIN): $(OBJ_FILES)
	if not exist "$(BIN_PATH)" $(MKDIR_P) $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES) $(LDFLAGS)

obj/main.o : $(SRC_FILES) src/main.c
	if not exist "$(@D)" $(MKDIR_P) "$(@D)"
	$(CC) -c src/main.c -o obj/main.o $(CFLAGS) $(INC_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	if not exist "$(@D)" $(MKDIR_P) "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)

clean:
	del $(OBJ_FILES) $(BIN_PATH)\$(APP_BIN)
else
CC = gcc
CFLAGS = -Wall

OS := $(shell uname)
ifeq ($(OS),Darwin)
	LDFLAGS =-I/Library/Frameworks/SDL.frameworks/Headers SDLmain.m -framework SDL -framework Cocoa -framework OpenGL
else
	LDFLAGS = -lSDL -lm -lGLU -lGL
endif

APP_BIN = Hovercraft

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = -I include
BIN_PATH = bin
LIB_PATH = lib

SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.c')
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))

all: $(APP_BIN)

$(APP_BIN): $(OBJ_FILES)
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES) $(LDFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)

clean:
	rm $(OBJ_FILES) $(BIN_PATH)/$(APP_BIN)

endif
