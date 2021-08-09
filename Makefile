##
## EPITECH PROJECT, 2021
## B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
## File description:
## Makefile
##

CC			= 	gcc

CFLAGS 		= 	-Wall -Wextra -ggdb3 -Iinclude

LDFLAGS		= 	-lcriterion --coverage

TEST_SRCS	=	$(wildcard ./tests/*.c) \
				./nm/sources/utils.c \
				./objdump/sources/utils.c

TEST_OBJS	=	$(TEST_SRCS:.c=.o)

SUBDIRS 	= 	nm objdump

all: 					$(SUBDIRS)

$(SUBDIRS):
						make -C $@

all clean fclean re:
						make -C objdump $@
						make -C nm $@

tests_run:				all $(TEST_OBJS)
						$(CC) $(CFLAGS) $(LDFLAGS) $(TEST_OBJS)
						./a.out

.PHONY: 				nm objdump all clean fclean re tests_run