#include "../../../include/Irc.hpp"

bool Server::_oper_cmd(User *user, std::string args)
{
	
	std::cout << "[DEBUG] oper args : " << args << std::endl;
	(void)user;
	return (true);
}
