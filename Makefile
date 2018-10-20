NAME = avm
SRC = main.cpp Calculator.cpp CreateFactory.cpp Instruction.cpp
OBJ = $(SRC:.cpp=.o)
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

obj: $(OBJ)

$(NAME) : $(OBJ)
	g++ $(OBJ) $(FLAGS) -o $(NAME)

%.o: %.c
	g++ $(FLAGS) -o $@ $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
