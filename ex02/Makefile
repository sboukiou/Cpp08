CXX=c++
CPPFLAGS=-Wall -Werror -Wextra -std=c++98
RM=rm -f

SRC=main.cpp
OBJ=$(SRC:%.cpp=%.o)
NAME=MutanStack

all:$(NAME)


$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
