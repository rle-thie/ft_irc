/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:29:33 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/06 19:55:35 by rle-thie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Irc.hpp"

int Server::_manageCmd(pollfd pfd, std::pair<std::string, std::string> cmd)
{
	// std::cout << "User" << _user_dict[pfd.fd]->getUserSd() << "<<--- = '" << cmd.first << "' > '" << cmd.second << "'" << std::endl;
	if (_user_dict[pfd.fd]->getCap() == false)
	{
		if (cmd.first != "CAP" || cmd.second[0] != 'L' || cmd.second[1] != 'S')
		{
			_sendError(_user_dict[pfd.fd], ERR_NOCAP);
			_disconnectUser(_user_dict[pfd.fd], 1);
			return 1;
		}
		else
			_user_dict[pfd.fd]->setCap(true);
		return 0;
	}
	else if (_user_dict[pfd.fd]->getAuth() == false && _user_dict[pfd.fd]->getCap() == true && _user_dict[pfd.fd]->getPassword() == "")
	{
		if (cmd.first != "PASS")
		{
			_sendError(_user_dict[pfd.fd], ERR_NOPASSWORD);
			_disconnectUser(_user_dict[pfd.fd], 1);
			return 1;
		}
		else if (cmd.first == "PASS" && cmd.second != _password)
		{
			_sendError(_user_dict[pfd.fd], ERR_WRONGPASSWORD);
			_disconnectUser(_user_dict[pfd.fd], 1);
			return (1);
		}
		else if (cmd.first == "PASS" && cmd.second == _password)
		{
			_sendRpl(_user_dict[pfd.fd], RPL_GOODPASS);
			_user_dict[pfd.fd]->setPass(cmd.second);
			return (0);
		}
	}
	else if (_user_dict[pfd.fd]->getAuth() == false && _user_dict[pfd.fd]->getCap() == true && _user_dict[pfd.fd]->getPassword() != "")
	{
		if (cmd.first == "USER" && _user_dict[pfd.fd]->getNick() == "")
		{
			_sendError(_user_dict[pfd.fd], ERR_NONICKNAMEAUTH);
			_disconnectUser(_user_dict[pfd.fd], 1);
			return 1;
		}
		else if (cmd.first == "USER" && _user_dict[pfd.fd]->getNick() != "")
		{
			_user_dict[pfd.fd]->setUser(cmd.second);
		}
	}
	if (_acceptConnection(_user_dict[pfd.fd], cmd) == false)
		return (1);
	if (_user_dict[pfd.fd]->getAuth() == false && _is_auth(_user_dict[pfd.fd]) == true)
	{
		// std::cout << "tesssst : " << _user_dict[pfd.fd]->getClient() << "____" << _user_dict[pfd.fd]->getNick() << std::endl;
		_sendRpl(_user_dict[pfd.fd], RPL_WELCOME(_user_dict[pfd.fd]->getClient(), _user_dict[pfd.fd]->getNick()));
		_sendRpl(_user_dict[pfd.fd], RPL_YOURHOST(_user_dict[pfd.fd]->getClient(), _user_dict[pfd.fd]->getNick()));
		_sendRpl(_user_dict[pfd.fd], RPL_CREATED(_user_dict[pfd.fd]->getClient(), _user_dict[pfd.fd]->getNick(), _creation_time));
		_sendRpl(_user_dict[pfd.fd], RPL_MYINFO(_user_dict[pfd.fd]->getClient(), _user_dict[pfd.fd]->getNick()));
	}
	return (0);
}