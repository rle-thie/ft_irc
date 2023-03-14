# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 08:42:57 by arudy             #+#    #+#              #
#    Updated: 2023/03/13 15:25:05 by rle-thie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ircserv

SRCS_CLASS = $(addprefix Class/, Server.cpp User.cpp)

DIR_SRCS = srcs

DIR_OBJS = objects

SRCS	= main.cpp ${SRCS_CLASS}

OBJS	= $(SRCS:%.cpp=$(DIR_OBJS)/%.o)

CC		= c++

RM		= rm -rf

MKDIR	= mkdir -p

CFLAGS	= -Wall -Werror -Wextra -pedantic -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(DIR_OBJS)/%.o : $(DIR_SRCS)/%.cpp
			${MKDIR} ${dir $@}
		${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} ${DIR_OBJS}

re: fclean all

ree: re
	./ircserv 2222 abcd

rc: re
	${RM} ${OBJS} && clear && ./ircserv 6667 lol

rv: re
	${RM} ${OBJS} && clear && valgrind --leak-check=full ./ircserv 6667 lol

v: all
	valgrind --leak-check=full ./ircserv 6667 lol

.PHONY: all clean fclean re rc rv v
