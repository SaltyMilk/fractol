NAME = fractol

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
MINILIBX_NAME = minilibx_linux
MINILIBX_PATH = ./minilibx_linux
endif
ifeq ($(UNAME), Darwin)
MINILIBX_NAME = minilibx_opengl
MINILIBX_PATH = ./minilibx_opengl
endif

SRC_PATH = srcs
SRC_NAME = main.c key_input.c mandelbrot.c juliaset.c thirdFract.c

OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror

CPPFLAGS = -Iincludes -Ilibft -I$(MINILIBX_NAME)
LDFLAGS = -Llibft -L$(MINILIBX_NAME)
# TODO Conditional if macOS or Linux
ifeq ($(UNAME), Linux)
LDLIBS = -lft -lmlx -lXext -lX11 -lm -lpthread
endif
ifeq ($(UNAME), Darwin)
LDLIBS = -lft -lmlx -lpthread -framework OpenGl -framework Appkit
endif

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: libft minilibx_all $(NAME)

$(NAME): $(OBJ) $(MINILIBX_NAME)/libmlx.a libft/libft.a includes/fractol.h
	@$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ) $(MINILIBX_NAME)/libmlx.a libft/libft.a -o $@
	@echo "Compilation of fractol:	\033[1;32mOK\033[m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -pv $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

libft:
	@make -C libft

clean:
	@make -C libft clean
	@make -C $(MINILIBX_PATH) clean
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean:
	@make -C libft fclean
	@make -C $(MINILIBX_PATH) clean
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)

re: fclean all

bonus: all

minilibx_all:
	make -C $(MINILIBX_PATH) all

.PHONY: all clean fclean re libft