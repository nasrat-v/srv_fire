
SRC		= launch_server.cpp

OBJ		= $(SRC:.cpp=.o)

NAME		= server_test

RM		= rm -f

CXXFLAGS		= -std=c++17 -W -Wall -Werror -Wextra -Wundef -Wpointer-arith -Wcast-align -Wcast-qual -Wunreachable-code

CC		= g++ -o

all:		compile

compile:	$(OBJ)
		$(CC) $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

