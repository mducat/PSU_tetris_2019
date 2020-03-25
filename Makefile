##
## EPITECH PROJECT, 2019
## tetris
## File description:
## Makefile
##

SRC	=	src/main.c		\
		src/args.c		\
		src/debug.c		\
		src/tetriminos.c	\
		src/string.c		\
		src/file.c		\
		src/array.c		\
		src/game.c		\
		src/draw.c		\
		src/logic.c		\
		src/blocks.c

OBJ	=	$(SRC:.c=.o)

NAME	=	tetris

CFLAGS	=	-Iinclude -Llib -lmy -lncurses

all:
	$(MAKE) -C lib/my --no-print-directory
	$(MAKE) -C lib/my clean --no-print-directory
	$(MAKE) $(NAME) --no-print-directory

$(NAME):$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

debug:
	gcc -g -o $(NAME) $(SRC) $(CFLAGS)

tests_run:
	$(MAKE) -C tests/ --no-print-directory
	./unit-tests

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./tests clean --no-print-directory

fclean:	clean
	rm -f lib/my/libmy.a lib/libmy.a
	rm -f $(NAME)
	$(MAKE) -C ./tests fclean --no-print-directory

re:	fclean all
