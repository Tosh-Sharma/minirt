NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Imlx
LIBFT_SRC_FILES = ft_isalpha.c \
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
		ft_strcmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
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

LIB_SRC = $(addprefix libft/, $(LIBFT_SRC_FILES))

SRCS = 	main.c \
		parser/parsing.c \
		parser/parsing_objects.c \
		parser/camera_and_lights.c \
		vector/initialization.c \
		vector/manipulation.c \
		utils/common_utils.c \
		utils/math_utils.c \
		drawing/ray_tracing.c \
		drawing/drawing_utils.c \
		drawing/virtual_screen.c \
		intersections/sphere.c \
		intersections/cylinder.c \
		intersections/plane.c \
		intersections/cone.c \
		intersections/disk.c \
		$(LIB_SRC)

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	make -C ./libft
	$(CC) $(OBJS) -lmlx -Lminilibx_opengl -framework OpenGL -framework AppKit -o $(NAME) libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

fclean: clean
	rm -f ${NAME}

clean:
	rm -f ${OBJS}

.PHONY: clean fclean re all