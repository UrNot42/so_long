NAME		=	libftprintf.a

SRCS		=	ft_printf.c ft_printf_puts.c libft/ft_strlen.c libft/ft_putstr_fd.c libft/ft_putchar_fd.c

OBJS		=	${SRCS:.c=.o}

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

%.o:			%.c
				${CC} ${CFLAGS} -Ilibft -c $< -o $@

all:			${NAME}

${NAME}:		${OBJS}
				ar rcs ${NAME} ${OBJS}

clean:
				rm -f ${OBJS}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

test:		${OBJS}
			${CC} ${OBJS} -o test

.PHONY:			all clean fclean re
