/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:15:44 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/07 00:21:11 by rle-thie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

#define RESET "\033[0m"
#define GRAS "\033[1m"
#define GREEN "\033[92m"
#define RED "\033[91m"
#define BLUE "\033[96m"

#define DIS_SEND GRAS "[IRC SERVER]" RESET GREEN" ----->> User"
#define DIS_SENDEND(str) (" : " + std::string(str) + RESET)
#define DIS_SENDERR GRAS "[IRC SERVER]" RESET RED " ----->> User"
#define DIS_SENDERREND(str) (" : " + std::string(str) + RESET)
#define DIS_RECV GRAS "[IRC SERVER]" RESET BLUE" User"
#define DIS_RECVEND(cmd, args) (" <<----- : " + std::string(cmd) + " " + std::string(args) + RESET)

// ERRORS
#define ERR_UNKNOWNCOMMAND(nickname, cmd) (":irc.42 421 " + std::string(nickname) + " " + std::string(cmd) + " :Unknown command \r\n")
#define ERR_NOCAP ":irc.42 400 : Connection refused, no CAP provided \r\n"
#define ERR_WRONGPASSWORD ":irc.42 400 : Connection refused, wrong password \r\n"
#define ERR_NOPASSWORD ":irc.42 400 : Connection refused, You're not connected \r\n"
#define ERR_NONICKNAMEAUTH ":irc.42 400 : Connection refused, No nickname provided, registration not completed\r\n"
#define ERR_NEEDMOREPARAMS (cmd, nickname)(":irc.42 461 " + std::string(nickname) + " " + std::string(cmd) + " :Not enough parameters\r\n")
// err de la cmd NICK
#define ERR_NONICKNAMEGIVEN(nickname) (":irc.42 431 " + std::string(nickname) + " :No nickname given\r\n")
#define ERR_NICKNAMEINUSE(nickname) (":433 " + std::string(nickname) + " :Nickname is already in use\r\n")
// err cmd USER
#define ERR_ALREADYREGISTRED(nickname) (":irc.42 462 " + std::string(nickname) + " :Unauthorized command (already registered)\r\n")

// REPLY
#define RPL_WELCOME(client, nickname) (":" + std::string(client) + " 001 " + std::string(nickname) + " :Welcome a tous mes srabs wallah\r\n")
#define RPL_YOURHOST(client, nickname) (":" + std::string(client) + " 002 " + std::string(nickname) + " :Your host is irc.42\r\n")
#define RPL_CREATED(client, nickname, crea_time) (":" + std::string(client) + " 003 " + std::string(nickname) + " :Server was created " + std::string(crea_time) + " \r\n")
#define RPL_MYINFO(client, nickname) (":" + std::string(client) + " 004 " + std::string(nickname) + " :irc.server 1.0 io kl\r\n")
#define RPL_GOODPASS GREEN "Connection accepted !" RESET "\r\n"
#define RPL_NICKSUCCES(nick) ("You're now known as " + std::string(nick) + "!\r\n")
#define RPL_PONG(args)("PONG " + std::string(args) + "\r\n")
#define RPL_PONGEMPTY "PONG\r\n"


// RPL_MYINFO
// "irc.server" est le nom du serveur IRC.
// "1.0" fait référence à la version 1.0 du logiciel du serveur IRC utilisé.
// "io" indique que le serveur prend en charge les fonctionnalités "input/output" étendues. Cela peut signifier qu'il supporte des extensions de protocole ou des fonctionnalités spécifiques supplémentaires pour faciliter les entrées/sorties.
// "kl" suggère que le serveur prend en charge les modes "K-line". Les K-lines sont utilisées pour bloquer les utilisateurs ou les serveurs spécifiques de se connecter au réseau IRC.
