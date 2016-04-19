CC = g++
#CC = clang
FLAGS = -std=c++11 -Wall -pedantic
CPP_FILES := $(wildcard src/*.cpp)
SDL_DIR = "include/SDL2-2.0.4"
SDL_IMG_DIR = "include/SDL2_image-2.0.1"
SDL_TTF_DIR = "include/SDL2_ttf-2.0.13"
INCLUDES = -I $(SDL_DIR)"/include" -I $(SDL_IMG_DIR)"/include"  -I $(SDL_TTF_DIR)"/include" 
LIBRARIES = -L $(SDL_DIR)"/lib/x86" -L$(SDL_IMG_DIR)"/lib/x86" -L$(SDL_TTF_DIR)"/lib/x86"
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -mwindows
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
build/main.exe: $(OBJ_FILES)
	$(CC) $(FLAGS) -o $@ $^ $(LIBRARIES) $(INCLUDES) $(LINKER_FLAGS)
obj/%.o: src/%.cpp
	$(CC) $(FLAGS) -c -o $@ $< $(LIBRARIES) $(INCLUDES) $(LINKER_FLAGS)
clean:
	rm -f obj/*.o *.out
