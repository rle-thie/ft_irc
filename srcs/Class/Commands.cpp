/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:29:33 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/05 00:25:09 by rle-thie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Irc.hpp"

int Server::_manageCmd(pollfd pfd, std::pair<std::string, std::string> cmd)
{
	if (_user_dict[pfd.fd]->getAuth() == true)
		_acceptConnection(_user_dict[pfd.fd], cmd);
	else if (cmd.first == "CAP")
		return 1;
	if (_user_dict[pfd.fd]->getAuth() == false)
	{
		if (cmd.first == "PASS")
		{
			std::cout << "Mot de passe envoye : " << cmd.second << std::endl;
			_user_dict[pfd.fd]->setPass(cmd.second);
		}
		else if (cmd.first == "NICK")
		{
			std::cout << "Nick envoye : " << cmd.second << std::endl;
			_user_dict[pfd.fd]->setNick(cmd.second);
		}
		else if (cmd.first == "USER")
		{
			std::cout << "User envoye : " << cmd.second << std::endl;
			_user_dict[pfd.fd]->setUser(cmd.second);
		}
		_is_auth(_user_dict[pfd.fd]);
	}
	
	// else if (cmd.first == "NICK")
	return 1;
}