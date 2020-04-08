##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile for 42sh Lib
##

SHELL	=	sh

HEADER	=	my.h

LIBSRC	=	my_strlen.c					\
			my_strcmp.c					\
			my_strdup.c					\
			my_getnbr.c					\
			my_sprintf.c				\
			destroy.c					\
			int_to_str_static.c			\
			str_to_word_array.c			\
			get_next_line.c				\

LIBOBJ	=	$(LIBSRC:.c=.o)

NAME	=	libmy.a

all:		$(NAME)

$(NAME):	$(LIBOBJ)
			ar rc $(NAME) $(LIBOBJ)

clean:
			rm -f $(LIBOBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean	all

.PHONY:		all clean fclean re
