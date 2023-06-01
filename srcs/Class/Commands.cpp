/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:29:33 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/01 20:37:44 by rle-thie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Irc.hpp"

int Server::_manageCmd(pollfd pfd, std::pair<std::string, std::string> cmd)
{
	int ret;

	if (_user_dict[pfd.fd]->getFirstTry())
		if ((ret = _acceptConnection(_user_dict[pfd.fd], cmd)))
			return ret;
	if (cmd.first == "CAP")
		return 0;
	if (_commands.find(cmd.first) != _commands.end())
		return (this->*_commands[cmd.first])(_user_dict[pfd.fd], cmd.second);
	return 3;
}