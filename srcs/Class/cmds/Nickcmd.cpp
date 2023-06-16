#include "../../../include/Irc.hpp"

static bool containsSpace(const std::string& input)
{
    std::string::size_type spacePos = input.find(' ');
    return (spacePos != std::string::npos);
}

bool Server::_nick_cmd(User *user, std::string args)
{
	std::cout << "[DEBUG] Nick stocked : " << args << std::endl;
	if (user->getAuth() == true)
	{
		if (args.empty())
		{
			_sendError(user, ERR_NONICKNAMEGIVEN(user->getNick()));
			return (false);
		}
		if (_find_user(args) != NULL)
		{
			_sendError(user, ERR_NICKNAMEINUSE(args));
			return (false);
		}
		if (containsSpace(args))
		{
			_sendError(user, ERR_WRONGNICKNAME);
			return (false);
		}
		std::string old = user->getNick();
		user->setNick(args);
		_sendRpl(user, RPL_NICK(old, args));
	}
	else
	{
		if (user->getCap() == true && user->getPassword() != "")
		{
			if (args.empty())
			{
				_sendError(user, ERR_NONICKNAMEGIVEN(user->getNick()));
				_disconnectUser(user, 1);
				return (false);
			}
			if (_find_user(args) != NULL)
			{
				_sendError(user, ERR_NICKNAMEINUSE(args));
				_disconnectUser(user, 1);
				return (false);
			}
			if (containsSpace(args))
			{
				_sendError(user, ERR_WRONGNICKNAME);
				_disconnectUser(user, 1);
				return (false);
			}
			std::string old = user->getNick();
			user->setNick(args);
			_sendRpl(user, RPL_NICK(old, args));
		}
	}
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
