#include "../../../include/Irc.hpp"

void Server::_quit_cmd(User *user, std::string args)
{
	(void)user;
	std::cout << "[DEBUG] ta mere la pute quit stocked : " << args << std::endl;
}