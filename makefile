CC = clang++
BUILD = bin
TARG := $(BUILD)
DATE = $(shell date '+%Y-%m-%d' )
FILE := test-$(DATE)
CFLAG := -std=c++17 -Ofast -I include
LFLAG := -lpthread -lraylib -lenet 

ifeq ($(OS),Windows_NT)
	CC := clang++
	PLAT := Windows
	LFLAG += -Wl,--allow-multiple-definition -lopengl32 -lgdi32 -lwinmm -L lib/Windows -lws2_32 -fopenmp
else
	OS = $(shell uname -s)
	ifeq ($(OS), Linux)
		PLAT := Linux
		LFLAG += -L lib/Linux -lGL -lm -ldl -lrt -lX11
	else
		PLAT := Mac
		CFLAG += -I /opt/homebrew/include
		LFLAG += -lomp -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -L lib/Mac -L /opt/homebrew/lib
	endif
endif

OBJ = $(patsubst src/%.cpp,$(BUILD)/$(PLAT)/%.o,$(wildcard src/*.cpp))
TARG := $(TARG)/$(PLAT)/$(FILE)

all: $(TARG) $(OBJ)

$(TARG):$(OBJ)
	$(CC) -o $(TARG) $(OBJ) $(LFLAG)

$(OBJ): bin/$(PLAT)/%.o:src/%.cpp
	$(CC) -c $(CFLAG) $< -o $@

clean:
	rm $(BUILD)/$(PLAT)/*.o
	rm $(TARG)

updategit:
	git commit -m "Updating sources $(DATE)"
	git push -u origin master

getinfo:
	echo $(OS)
	echo $(PLAT)

date:
	echo $(DATE)

init:
	mkdir $(BUILD)
	mkdir $(BUILD)/$(PLAT)