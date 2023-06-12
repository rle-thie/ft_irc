/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevy <ldevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:15:44 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/13 00:08:14 by ldevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

#define RESET "\033[0m"
#define GRAS "\033[1m"
#define GREEN "\033[92m"
#define RED "\033[91m"
#define BLUE "\033[96m"

#define DIS_SEND GRAS "[IRC SERVER]" RESET GREEN " ----->> User"
#define DIS_SENDEND(str) (" : " + std::string(str) + RESET)
#define DIS_SENDERR GRAS "[IRC SERVER]" RESET RED " ----->> User"
#define DIS_SENDERREND(str) (" : " + std::string(str) + RESET)
#define DIS_RECV GRAS "[IRC SERVER]" RESET BLUE " User"
#define DIS_RECVEND(cmd, args) (" <<----- : " + std::string(cmd) + " " + std::string(args) + RESET)

// ERRORS
#define ERR_UNKNOWNCOMMAND(nickname, cmd) (":irc.42 421 " + std::string(nickname) + " " + std::string(cmd) + " :Unknown command \r\n")
#define ERR_NOCAP ":irc.42 400 : Connection refused, no CAP provided \r\n"
#define ERR_WRONGPASSWORD ":irc.42 400 : Connection refused, wrong password \r\n"
#define ERR_NOPASSWORD ":irc.42 400 : Connection refused, You're not connected \r\n"
#define ERR_NONICKNAMEAUTH ":irc.42 400 : Connection refused, No nickname provided, registration not completed\r\n"
#define ERR_NEEDMOREPARAMS(cmd, nickname) (":irc.42 461 " + std::string(nickname) + " " + std::string(cmd) + " :Not enough parameters\r\n")
// err de la cmd NICK
#define ERR_NONICKNAMEGIVEN(nickname) (":irc.42 431 " + std::string(nickname) + " :No nickname given\r\n")
#define ERR_NICKNAMEINUSE(nickname) (":433 " + std::string(nickname) + " :Nickname is already in use\r\n")
// err cmd USER
#define ERR_ALREADYREGISTRED(nickname) (":irc.42 462 " + std::string(nickname) + " :Unauthorized command (already registered)\r\n")
// err cmd OPER
#define ERR_PASSWDMISMATCH(nickname) (":irc.42 464 " + std::string(nickname) + " :Password incorrect\r\n")
// err cmd prvmsg
#define ERR_NORECIPIENT(nickname, cmd) (":irc.42 411 " + std::string(nickname) + ":No recipient given (" + std::string(cmd) + ")\r\n")
#define ERR_CANNOTSENDTOCHAN(nickname, channel)(":irc.42 404 " + std::string(nickname) + ":" + std::string(channel) + " :Cannot send to channel\r\n")
#define ERR_NOTEXTTOSEND(nickname) (":irc.42 412 " + std::string(nickname) + " :No text to send\r\n")
#define ERR_NOSUCHNICK(target, nickname) (":irc.42 401 " + std::string(nickname) + " :" + std::string(target) + " :No such nick/channel\r\n")
//general error msg
#define ERROR RED ":irc.42 ERROR :Internal server error"
#define ERR_NOTONCHANNEL(nickname, channel) (":irc.42 442 " + std::string(nickname) + " " + std::string(channel) + " :You're not on that channel\r\n")
//	err cmd kick
#define ERR_NOSUCHCHANNEL(nickname, channel) (":irc.42 403 " + std::string(nickname) + " " + std::string(channel) + " :No such channel\r\n")
#define ERR_CHANOPRIVSNEEDED(nickname, channel) (":irc.42 482 " + std::string(nickname) + " " + std::string(channel) + " :You're not channel operator\r\n")
#define ERR_USERNOTINCHANNEL(nickname, channel, target) (":irc.42 441 " + std::string(nickname) + " " + std::string(target) + " " + std::string(channel) + " :They aren't on that channel\r\n")
// err cmd 
#define ERR_USERSDONTMATCH(nickname) (":irc.42 502 " + std::string(nickname) + " :Cannot change mode for other users\r\n")
#define ERR_UMODEUNKNOWNFLAG(nickname) (":irc.42 501 " + std::string(nickname) + " :Unknown MODE flag\r\n")
// err join
#define ERR_CHANNELISFULL(nickname, channel) (":irc.42 501 " + std::string(nickname) + " " + std::string(channel) + " :Cannot join channel (+l)\r\n")
// REPLY
#define RPL_YOUREOPER(nickname) (":irc.42 381 " + std::string(nickname) + " :You are now an IRC operator\r\n")
#define RPL_WELCOME(client, nickname) (":" + std::string(client) + " 001 " + std::string(nickname) + " :Welcome a tous mes srabs wallah\r\n")
#define RPL_YOURHOST(client, nickname) (":" + std::string(client) + " 002 " + std::string(nickname) + " :Your host is irc.42\r\n")
#define RPL_CREATED(client, nickname, crea_time) (":" + std::string(client) + " 003 " + std::string(nickname) + " :Server was created " + std::string(crea_time) + " \r\n")
#define RPL_MYINFO(client, nickname) (":" + std::string(client) + " 004 " + std::string(nickname) + " :irc.server 1.0 io kl\r\n")
#define RPL_GOODPASS GREEN "Connection accepted !" RESET "\r\n"
#define RPL_NICKSUCCES(nick) ("You're now known as " + std::string(nick) + "!\r\n")
#define RPL_PONG(args) ("PONG " + std::string(args) + "\r\n")
#define RPL_PONGEMPTY "PONG\r\n"
#define MESSAGE(nickname, username, hostname, targetnick, message) (":" + std::string(nickname) + "!" + std::string(username) + "@" + std::string(hostname) + " PRIVMSG " + std::string(targetnick) + " :" + std::string(message) + "\r\n")
#define MESSAGE_CMD(nickname, username, hostname, targetnick, channel, cmd, message) (":" + std::string(nickname) + "!" + std::string(username) + "@" + std::string(hostname) + " " + std::string(cmd) + " " + std::string(channel) + " " + std::string(targetnick) + " :" + std::string(message) + "\r\n")
#define MESSAGE_KICK(channel, nickname, msg) (":irc.42 KICK " + std::string(channel) + " " + std::string(nickname) + " :" + std::string(msg) + ".\r\n")
#define RPL_JOIN(client, chan_name) (":" + std::string(client) + " JOIN :" + std::string(chan_name) + "\r\n")
#define RPL_NAMEREPLY(client, nickname, chan_name, usernames) (":" + std::string(client) +" 353 " + std::string(nickname) + " = " + std::string(chan_name) + " :" + std::string(usernames) + "\r\n")
#define RPL_ENDOFNAMES(client, nickname, chan_name) (":" + std::string(client) +" 366 " + std::string(nickname) + " " + std::string(chan_name) + " :End of /NAMES list\r\n")
// #define PRL_UMODEIS(msg) (":irc.42 221 yourNick +iwx :+i")

// RPL_MYINFO
// "irc.server" est le nom du serveur IRC.
// "1.0" fait référence à la version 1.0 du logiciel du serveur IRC utilisé.
// "io" indique que le serveur prend en charge les fonctionnalités "input/output" étendues. Cela peut signifier qu'il supporte des extensions de protocole ou des fonctionnalités spécifiques supplémentaires pour faciliter les entrées/sorties.
// "kl" suggère que le serveur prend en charge les modes "K-line". Les K-lines sont utilisées pour bloquer les utilisateurs ou les serveurs spécifiques de se connecter au réseau IRC.
