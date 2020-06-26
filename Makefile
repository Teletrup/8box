.PHONY: run clean

NAME = 8box
CC = g++
EXT = cpp
BINF = -lGL -lGLEW -lglfw3 -ldl -lX11 -lpthread -lm
OBJF = -O3
INC = 

SRC = $(wildcard src/*.$(EXT))
OBJ = $(SRC:src/%.c=obj/%.o)

bin/$(NAME): src bin obj $(OBJ) $(SRC)
	$(CC) $(OBJ) $(BINF) -o bin/$(NAME)

deps:
	echo -e "$(foreach F, $(SRC), obj/$$($(CC) -MM $(F))\n\t$(CC) $(INC) -c $(F) -o $(F:src/%.$(EXT)=obj/%.o)\n)" > deps

bin:
	mkdir bin

obj:
	mkdir obj

run: bin/$(NAME)
	@ cd bin && ./$(NAME) $(ARGS)

clean:
	- rm -r bin/$(NAME) obj deps

update:
	rm deps

-include deps
