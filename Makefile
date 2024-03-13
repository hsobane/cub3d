SRC = game/cub3d.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3d
INC = includes/cub3d.h mlx/mlx.h
INC_CUB = includes

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(INC_CUB) -o $(NAME) $(OBJ) -Lmlx -lmlx -lXext -lX11 -lm -lz

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -I$(INC_CUB) -c $< -o $@

bonus: all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re all clean fclean bonus