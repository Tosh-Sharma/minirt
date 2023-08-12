NAME ?= libft.a
CC ?= gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_cpyarray.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_superatoi.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putunbr_fd.c \
		ft_putnbr_16.c \
		ft_putnbr_16_caps.c \
		ft_revstr.c \
		ft_straddchar.c \
		list_manipulation/ft_lstnew.c \
		list_manipulation/ft_lstadd_front.c \
		list_manipulation/ft_lstsize.c \
		list_manipulation/ft_lstlast.c \
		list_manipulation/ft_lstadd_back.c \
		list_manipulation/ft_lstdelone.c \
		list_manipulation/ft_lstclear.c \
		list_manipulation/ft_lstiter.c \
		list_manipulation/ft_lstmap.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		flags/spaces.c \
		printers/ft_printf.c \
		printers/pf_putchar.c \
		printers/pf_putnbr.c \
		printers/pf_putpointer.c \
		printers/pf_putstr.c \
		printers/pf_putunbr.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

%.o: %.c
	${CC} ${CFLAGS} -o ${@} -c ${@:.o=.c}

re: fclean all

fclean: clean
	rm -f ${NAME}

clean:
	rm -f ${OBJS} ${BONUS_OBJS}

.PHONY: clean fclean re all
