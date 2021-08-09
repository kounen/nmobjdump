##
## EPITECH PROJECT, 2021
## B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
## File description:
## Makefile my_objdump
##

NAME 		=	my_objdump

CC			=	gcc

CFLAGS		=	-Wall -Wextra -ggdb3 -Iinclude

RM			=	rm -f

MV			=	mv

SRCS		=	$(wildcard ./sources/*.c)

OBJS		=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			$(MV) $(NAME) ../

clean:		
			$(RM) $(OBJS)

fclean:		clean
			$(RM) ../$(NAME)

re:			fclean all

.PHONY:		all clean fclean re