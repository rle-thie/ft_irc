#include "../../../include/Irc.hpp"

bool Server::_nick_cmd(User *user, std::string args)
{
	std::cout << "[DEBUG] Nick stocked : " << args << std::endl;
	if (args.empty())
	{
		_sendError(user, ERR_NONICKNAMEGIVEN(user->getNick()));
		return (false);
	}
	if (_find_user(args) != NULL)
	{
		_sendError(user, ERR_NICKNAMEINUSE(user->getNick()));
		return (false);
	}
	user->setNick(args);
	_sendRpl(user, RPL_NICKSUCCES(args));
	return (true);
}

User* Server::_find_user(std::string nickname)
{
	std::map<int, User*>::iterator node;
	for (node = _user_dict.begin(); node != _user_dict.end(); node++)
	{
		if (node->second->getNick() == nickname)
			return (node->second);
	}
	return (NULL);
}