#include "../../../include/Irc.hpp"

bool Server::_user_cmd(User *user, std::string args)
{
	std::cout << "[DEBUG] USER cmd : " << args << std::endl;
	if (user->getAuth() || !user->getUserName().empty())
	{
		_sendError(user, ERR_ALREADYREGISTRED(user->getNick()));
		return (false);
	}
	return (true);
}
