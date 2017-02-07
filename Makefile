CC	= gcc

RM	= rm -f

CFLAGS	= -Wall -Wextra -ansi
LIB	=

NAME	= color_flood

SRCS	= src/main.c

OBJS	= $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LIB)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
