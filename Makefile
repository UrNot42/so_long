NAME		=	so_long

SRC_LIST	=	main.c \
				parsing.c \
				parsing_utils.c \
				game.c \
				world_map.c \
				world_puts.c \
				closing.c \
				rendering.c \
				pause_screen.c \
				pause_hooks.c \
				player.c \
				moving_obj.c \
				init_var.c \
				init_xpm.c \
				init_xpm_assets.c \
				keys.c \
				key_hooks.c \
				events_game.c \
				events_player.c \
				events_entity.c \
				events_key.c \
				map_tools.c \
				image_drawing.c \
				img_sprites.c \
				sprite_utils.c \
				create_img.c \
				anim.c \
				free_and_copy.c \
				free_images.c \
				tiles_utils.c \
				tiles_checking.c \
				tile_searching.c \
				tiles_is.c \
				printing.c \
				color.c \
				my_mlx_tools.c \
				my_mlx_win_tools.c \
				launching_utils.c \
				msg.c

SRCS_GNL	=	get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c

HEADERS	=	src/so_long.h ft_printf/ft_printf.h src/get_next_line/get_next_line.h libft/libft.h

SRCS_ALL	=	$(SRC_LIST) $(SRCS_GNL)

SRCS		=	$(addprefix $(SRC_DIR), $(SRCS_ALL))

OBJS		=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

LDLIBS		=	-lm -L./obj -lmlx -lXext -lX11

RM			=	rm -f

SRC_DIR		=	src/

OBJ_DIR		=	obj/

all:	$(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
				$(CC) $(CFLAGS) -g -c $< $(LDLIBS) -o $@

debug:			$(OBJS) $(HEADERS)
				make -C libft/
				make -C ft_printf/
				make -C minilibx-linux/
				mv minilibx-linux/libmlx.a obj/
				mv libft/libft.a obj/
				mv ft_printf/libftprintf.a obj/
				$(CC) -o $(NAME) $(OBJS) -g3 -g $(LDLIBS) obj/libft.a obj/libftprintf.a

$(NAME):		$(OBJS) $(HEADERS)
				make -C libft/
				make -C ft_printf/
				make -C minilibx-linux/
				mv minilibx-linux/libmlx.a obj/
				mv libft/libft.a obj/
				mv ft_printf/libftprintf.a obj/
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS) obj/libft.a obj/libftprintf.a

clean:
				rm -f $(OBJS)
				make -C libft/ clean
				make -C ft_printf/ clean
				make -C minilibx-linux/ clean

fclean:			clean
				$(RM) $(NAME)
				$(RM) obj/libft.a
				$(RM) obj/libftprintf.a
				$(RM) obj/libmlx.a

re:				fclean all

bonus:			all

.PHONY:			all clean fclean re debug bonus
