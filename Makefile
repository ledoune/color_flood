CC	= gcc

RM	= rm -f

CFLAGS	= -Wall -Wextra -ansi 
LIB	=

NAME	= color_flood

SRCS	= $(wildcard *.c)

OBJS	= $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LIB)

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
