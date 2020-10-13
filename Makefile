DIR =src
CXX=g++ -Wall -pedantic
FLAGS=-lncurses
NAME=havasiva
DOC=doc

ODIR=bin

_DEPS = application.h game.h map.h field.h empty.h mountain.h water.h tree.h woodcutter.h fishingbooth.h quary.h menu.h barracks.h cost.h objective.h castle.h house.h tutorial.h gamefiles.h readinput.h
DEPS = $(patsubst %,$(DIR)/%,$(_DEPS))

_OBJ = main.o application.o game.o map.o field.o empty.o woodcutter.o fishingbooth.o quary.o menu.o barracks.o cost.o objective.o castle.o house.o tutorial.o gamefiles.o readinput.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(DIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(FLAGS)

compile:
	mkdir -p $(ODIR)
	make _compile

_compile: $(OBJ)
	$(CXX) -o $(NAME) $^ $(FLAGS)

run:
	./$(NAME)

doc:
	doxygen Doxyfile

make all:
	make compile
	make doc

clean:
	rm -rf $(ODIR)
	rm -rf $(DOC)
	rm -f $(NAME)
