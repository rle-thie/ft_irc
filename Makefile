# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 08:42:57 by arudy             #+#    #+#              #
#    Updated: 2023/06/10 00:08:02 by rle-thie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ircserv

SRCS_CLASS = $(addprefix Class/, Server.cpp User.cpp Commands.cpp Utils.cpp Channel.cpp)

SRCS_CMDS = $(addprefix Class/cmds/, Invitecmd.cpp Joincmd.cpp Kickcmd.cpp Modecmd.cpp Nickcmd.cpp Opercdm.cpp Passcmd.cpp Pingcmd.cpp Privmsg.cpp Quitcmd.cpp Usercmd.cpp)

DIR_SRCS = srcs

DIR_OBJS = objects

SRCS	= main.cpp ${SRCS_CLASS} ${SRCS_CMDS}

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
	./ircserv 2222 aaa

reev: re
	valgrind --leak-check=full ./ircserv 2222 aaa

rc: re
	${RM} ${OBJS} && clear && ./ircserv 2222 aaa

rv: re
	${RM} ${OBJS} && clear && valgrind ./ircserv 2222 aaa

v: all
	valgrind --leak-check=full ./ircserv 2222 aaa

.PHONY: all clean fclean re rc rv v
