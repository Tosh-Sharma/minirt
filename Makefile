NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB = libft.a
SRCS = 	main.c \
 
OBJS = ${SRCS:.c=.o}

.c.o:
	$(CC) $(CFLAGS) -c $< -Ilibft

all: ${NAME}

${NAME}: ${OBJS}
	make -C ./libft
	mv libft/${LIB} .
	${CC} ${CFLAGS} $(OBJS) $(LIB) -o $(NAME)

%.o: %.c
	${CC} ${CFLAGS} -o ${@} -c ${@:.o=.c}

re: fclean all

fclean: clean
	rm -f ${NAME}

clean:
	rm -f ${OBJS} $(LIB) file*

.PHONY: clean fclean re all