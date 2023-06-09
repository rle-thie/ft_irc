#include "../../include/Irc.hpp"

int Server::_sendError(User *user, std::string err)
{
	_sendAll(user->getUserSd(), err.c_str(), err.length(), 0);
	// std::cout << "error..." << std::endl;
	std::cout << DIS_SENDERR << user->getUserSd() << DIS_SENDERREND(err) << std::endl;
	return 1;
}

int Server::_sendRpl(User *user, std::string strtosend)
{
	_sendAll(user->getUserSd(), strtosend.c_str(), strtosend.length(), 0);
	// std::cout << "\033[1m\033[96m[IRC SERVER]\033[0m --->> '" << strtosend << "'" << std::endl;
	std::cout << DIS_SEND << user->getUserSd() << DIS_SENDEND(strtosend) << std::endl;
	return 1;
}

int Server::_sendAll(int fd, const char *buf, size_t len, int flags)
{
	size_t sent = 0;
	size_t toSend = len;
	int ret = 0;

	while (sent < len) {
		// send() permettent de transmettre un message à destination d'une autre socket
		ret = send(fd, (buf + sent), toSend, flags);
		if (ret == -1)
			return ret;
		sent += ret;
		toSend -= ret;
	}
	return 0;
}

bool	Server::_is_auth(User *usr)
{
	std::cout << GRAS "[IRC SERVER]" RESET " checking for auth..." << std::endl;
	if (usr->getNick() != "" && usr->getUserName() != "" && usr->getPassword() != "")
	{
		if (usr->getAuth() == false)
		{
			std::cout << GRAS "[IRC SERVER] " RESET << usr->getNick() << " is now auth" << std::endl;
			usr->setAuth(true);
			// return (_disconnectUser(usr, 0));
		}
		return (1);
	}
	// std::cout << "[DEBUG] not ok for auth..." << std::endl;
	return (0);
}

Channel	*Server::_already_channel_name(std::string name)
{
	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		if (name == (*it)->getName())
			return (*it);
	}
	return (NULL);
}

void	Server::_delUserFromAllChann(User *user)
{
	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		(*it)->_delUser(user);
	}
}

void	Server::_delEmptyChannels()
{
	std::vector<Channel*>::iterator it = _channels.begin();
	std::vector<Channel*>::iterator to_del;
	for (; it != _channels.end();)
	{
		if ((*it)->getSizeConnected() == 0)
		{
			to_del = it;
			// it++;
			delete *to_del;
			_channels.erase(to_del);

		}
		else
			it++;
	}
}