SRC_CORE	=	main.cpp \
			$(wildcard network/src/*.cpp) \
			$(wildcard network/include/*.hpp) \
			$(wildcard Utilitary\*.hpp)

OBJ_CORE	=	$(SRC_CORE:.cpp=.o) \
			$(SRC_CORE:.hpp=.o)

NAME_CORE	=	core

LIB_CORE	=	-lpthread -lcurl -lcurlpp

CXXFLAGS	=	-std=gnu++17

all:			$(core)

core:		$(OBJ_CORE)
		g++ -o $($NAME_CORE) $(OBJ_CORE) $(LIB_CORE)

clean:
		rm  $(OBJ_CORE)
		rm  *~
		rm  network/src/*~
		rm  network/include/*~

fclean:
		clean
		rm $(NAME_CORE)
