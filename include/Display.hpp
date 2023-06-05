/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevy <ldevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:15:44 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/05 19:17:49by ldevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

#define DIS_RECV "[ircserv] Recv <- [user "
#define DIS_RECVEND(cmd, args) ("]:    " + std::string(cmd) + " " + std::string(args))

// ERRORS
#define ERR_UNKNOWNCOMMAND(client, nickname, cmd) (":" + std::string(client) + " 421 " + std::string(nickname) + " " + std::string(cmd) + " :Unknown command \r\n")

// REPLY
#define RPL_WELCOME(client, nickname) (":" + std::string(client) + " 001 " + std::string(nickname) + "\r\n")

// err de la cmd NICK
#define ERR_NONICKNAMEGIVEN(nickname) (":irc.42 431 " + std::string(nickname) + " :No nickname given")
#define ERR_NICKNAMEINUSE(nickname) (":irc.42 433 " + std::string(nickname) + " :Nickname is already in use")