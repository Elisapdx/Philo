NAME = philo
CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -f

SRCS =  init.c \
		main.c \
		ritual.c \
		threads.c \
		utils.c \


OBJC = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJC}
	${CC} ${CFLAGS} ${OBJC} -o ${NAME}

clean:
	 ${RM} ${OBJC}

fclean: clean
	${RM} ${NAME}

re: fclean all