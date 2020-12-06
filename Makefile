SRC = main.c key_input.c mandelbrot.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror -framework OpenGl -I libft -I mlx\
		-framework Appkit -lpthread -L mlx -lmlx -L libft -lft
MOBJ = $(SRC:.c=.o)

NAME = fractol

all : $(NAME)

$(NAME) : $(SRC) fractol.h
	cd libft && make bonus && cd ..	
	cd mlx && make && cd ..
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

bonus : all

clean : 
	rm -f libft/*.o
fclean :
	rm -f libft/*.o mlx/*.a mlx/*.o libft/*.a rm $(NAME)

re : fclean all

.PHONY : clean fclean re reb bonus all

