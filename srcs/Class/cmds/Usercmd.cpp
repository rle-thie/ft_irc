#include "../../../include/Irc.hpp"

bool Server::_user_cmd(User *user, std::string args)
{
	std::cout << "[DEBUG] USER cmd : " << args << std::endl;
	user=user;
	// if (user->getAuth() && !user->getUserName().empty())
	// {
	// 	_sendError(user, ERR_ALREADYREGISTRED(user->getNick()));
	// 	// _disconnectUser(user, 1);
	// 	return (false);
	// }
	// else if 
	return (true);
}
