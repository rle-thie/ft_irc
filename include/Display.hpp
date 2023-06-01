/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:15:44 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/01 19:54:45 by rle-thie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

#define DIS_RECV "[ircserv] Recv    <--    [Client "
#define DIS_RECVEND(cmd, args) ("]:    " + std::string(cmd) + " " + std::string(args))

// ERRORS
#define ERR_UNKNOWNCOMMAND(client, nickname, cmd) (":" + std::string(client) +" 421 " + std::string(nickname) + " " + std::string(cmd) + " :Unknown command \r\n")
