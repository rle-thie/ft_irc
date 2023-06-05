/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:15:44 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/05 20:14:17 by rle-thie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

#define DIS_RECV "[ircserv] Recv <- [user "
#define DIS_RECVEND(cmd, args) ("]:    " + std::string(cmd) + " " + std::string(args))

// ERRORS
#define ERR_UNKNOWNCOMMAND(client, nickname, cmd) (":" + std::string(client) + " 421 " + std::string(nickname) + " " + std::string(cmd) + " :Unknown command \r\n")
// err de la cmd NICK
#define ERR_NONICKNAMEGIVEN(nickname) (":irc.42 431 " + std::string(nickname) + " :No nickname given")
#define ERR_NICKNAMEINUSE(nickname) (":irc.42 433 " + std::string(nickname) + " :Nickname is already in use")

// REPLY
#define RPL_WELCOME(client, nickname) (":" + std::string(client) + " 001 " + std::string(nickname) + " :Welcome a tous mes srabs wallah\r\n")
#define RPL_YOURHOST(client, nickname)(":" + std::string(client) + " 002 " + std::string(nickname) + " :Your host is irc.42\r\n")
#define RPL_CREATED(client, nickname, crea_time)(":" + std::string(client) + " 003 " + std::string(nickname) + " :Server was created " + std::string(crea_time) + " \r\n")
#define RPL_MYINFO(client, nickname) (":" + std::string(client) + " 004 " + std::string(nickname) + " :irc.server 1.0 io kl\r\n")


// RPL_MYINFO
// "irc.server" est le nom du serveur IRC.
// "1.0" fait référence à la version 1.0 du logiciel du serveur IRC utilisé.
// "io" indique que le serveur prend en charge les fonctionnalités "input/output" étendues. Cela peut signifier qu'il supporte des extensions de protocole ou des fonctionnalités spécifiques supplémentaires pour faciliter les entrées/sorties.
// "kl" suggère que le serveur prend en charge les modes "K-line". Les K-lines sont utilisées pour bloquer les utilisateurs ou les serveurs spécifiques de se connecter au réseau IRC.
