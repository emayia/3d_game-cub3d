NAME	=	cub3d

SRCS	=	draw/draw3d.c			\
			keys/exit.c				\
			keys/keys.c				\
			moves/movements.c		\
			moves/rotations.c		\
			raycast/h_walls.c		\
			raycast/raycast.c		\
			raycast/v_walls.c		\
			raycast/walls.c			\
			GNL/get_next_line.c GNL/get_next_line_utils.c Utils/ft_strdup.c Utils/ft_strcmp.c \
			Utils/ft_atoi.c Utils/ft_split.c Utils/ft_isdigit.c Utils/ft_strjoin.c main.c Utils/ft_putstr_fd.c \
			Parsing/setarg.c Error/errormsg.c utils/ft_colorcheck.c utils/ft_strncpy.c \
			Parsing/setargbis.c Parsing/setargbistwo.c Parsing/mapprep.c Error/errormsgmap.c Parsing/namecheck.c \
			Parsing/set_row_col.c Parsing/set_map.c	\

OBJS	=	${SRCS:.c=.o}

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra -g -fsanitize=address

RM		=	rm -f

MLX		=	-Lmlx -lmlx -framework OpenGL -framework AppKit

all:		${NAME}

${NAME}:	${OBJS}
			make -C mlx
			${CC} ${CFLAGS} ${OBJS} ${MLX} -o ${NAME}
clean:
			${RM} ${OBJS}
			make clean -C mlx

fclean:		clean
			${RM} ${NAME}

re:			fclean all

norm:
			norminette $(SRCS) gnl/*.h minilib/*.h *.h

.PHONY:		all clean fclean re
