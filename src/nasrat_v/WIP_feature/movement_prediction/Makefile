
SRC		= draw.cpp \
		  mouse.cpp \
		  prediction.cpp \
		  log.cpp \
		  main.cpp


OBJ		= $(SRC:.cpp=.o)

NAME	= movement_prediction

RM		= rm -f

CXXFLAGS	= -std=c++17 -W -Wall -Wextra -Wundef -Wpointer-arith -Wcast-align -Wcast-qual -Wunreachable-code

OPENCVFLAGS	= -I /usr/include/opencv -L /usr/lib -lopencv_core -lopencv_imgproc -lopencv_highgui

CC		= g++ -o

all:	compile

compile:	$(OBJ)
		$(CC) $(NAME) $(OBJ) $(OPENCVFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
