#include "../../../include/Irc.hpp"

bool Server::_kick_cmd(User *user, std::string args)
{
	(void)args;
	std::cout  << "[DEBUG] user.nick " << user->getNick() << std::endl;
	std::cout  << "[DEBUG] user.username " << user->getUserName() << std::endl;
	std::cout  << "[DEBUG] user.hostname " << user->getHostName() << std::endl;
	return (true);
}