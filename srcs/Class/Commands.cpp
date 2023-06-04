/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:29:33 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/05 01:52:34 by rle-thie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Irc.hpp"

int Server::_manageCmd(pollfd pfd, std::pair<std::string, std::string> cmd)
{
	std::cout << "User" << _user_dict[pfd.fd]->getUserSd() << "<<--- = '" << cmd.first << "' > '" << cmd.second << "'" << std::endl;
	if (_user_dict[pfd.fd]->getAuth() == true)
		_acceptConnection(_user_dict[pfd.fd], cmd);
	else if (cmd.first == "CAP")
		return 1;
	if (_user_dict[pfd.fd]->getAuth() == false)
	{
		if (cmd.first == "PASS")
		{
			std::cout << "[DEBUG] Mot de passe stocked : " << cmd.second << std::endl;
			_user_dict[pfd.fd]->setPass(cmd.second);
		}
		else if (cmd.first == "NICK")
		{
			std::cout << "[DEBUG] Nick stocked : " << cmd.second << std::endl;
			_user_dict[pfd.fd]->setNick(cmd.second);
		}
		else if (cmd.first == "USER")
		{
			std::cout << "[DEBUG] User stocked : " << cmd.second << std::endl;
			_user_dict[pfd.fd]->setUser(cmd.second);
		}
		if (_is_auth(_user_dict[pfd.fd]) == 1)
		{
			_sendRpl(_user_dict[pfd.fd], RPL_WELCOME(_user_dict[pfd.fd]->getClient(), _user_dict[pfd.fd]->getNick()));
			// RPL_YOURHOST, RPL_CREATED, RPL_MYINFO
		}
	}
	
	// else if (cmd.first == "NICK")
	return 1;
}