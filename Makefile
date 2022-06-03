NAME = space_cake

SRC		=	source/main.c\
			source/draw.c\
			source/init.c\
			source/input.c\
			source/window.c\
			source/ennemis.c
			
OBJ 	=	$(SRC:.c=.o)

OBJ = $(SRC:.c=.o)

CFLAGS += -I./include
CFLAGS += -Wall -Werror -Wextra

LIBS += -lSDL2 -lSDL2_image -L/usr/local/lib

$(NAME): $(OBJ)
		$(CC) $(OBJ) $(LIBS) -o $(NAME)

# Règle permettant d'afficher les messages de debug (DEBUG_LOG)
debug: CFLAGS += -D__TEST
debug: re

all:    $(NAME)

clean:
		rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
