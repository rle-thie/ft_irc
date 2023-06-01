#include "../../include/Irc.hpp"

int Server::_sendError(User *user, std::string err)
{
	_sendAll(user->getUserSd(), err.c_str(), err.length(), 0);
	std::cout << DIS_ERR << user->getUserSd() << DIS_ERREND(err);
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