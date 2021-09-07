NAME	= pipex.a
PROG	= pipex

SRCS	= srcs/pipex.c\
		  srcs/helpers.c\

OBJS 	= ${SRCS:.c=.o}
MAIN	= srcs/pipex.c

HEADER	= -I./includes/

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror

.c.o:		%.o : %.c
					@gcc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

$(NAME):	${OBJS}
					@make re -C ./libft
					@cp libft/libft.a ./$(NAME)
					@ar -rcs ${NAME} ${OBJS}
					@$(CC) $(NAME) ${MAIN} -o ${PROG}

all: 		${NAME}

clean:
					@make clean -C ./libft
					@rm -f ${OBJS}
fclean: 	clean
					@make fclean -C ./libft
					@rm -f $(NAME)
					@rm -f ${PROG}

re:			fclean all