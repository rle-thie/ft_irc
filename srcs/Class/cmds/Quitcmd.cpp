#include "../../../include/Irc.hpp"

bool Server::_quit_cmd(User *user, std::string args)
{
	std::cout << "[DEBUG] quit cmd " << args << std::endl;
	_disconnectUser(user, 1);
	return (false);
}