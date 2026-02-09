CXX=c++
CPPFLAGS=-Wall -Werror -Wextra -std=c++98
RM=rm -f

SRC=main.cpp Span.cpp
OBJ=$(SRC:%.cpp=%.o)
NAME=Span

all:$(NAME)


$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
