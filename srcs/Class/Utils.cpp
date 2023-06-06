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
	std::cout << "[DEBUG] checking auth..." << std::endl;
	if (usr->getNick() != "" && usr->getUserName() != "" && usr->getPassword() != "")
	{
		if (usr->getAuth() == false)
		{
			std::cout << usr->getNick() << "[DEBUG] is now auth" << std::endl;
			usr->setAuth(true);
			// return (_disconnectUser(usr, 0));
		}
		return (1);
	}
	std::cout << "[DEBUG] not ok for auth..." << std::endl;
	return (0);
}