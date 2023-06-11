#include "../../../include/Irc.hpp"

bool Server::_kick_cmd(User *user, std::string args)
{
	std::vector<std::string> splitstring;
	std::vector<std::string> users_nicks;
	size_t spacePos;
	size_t startPos = 0;


	spacePos = args.find(' ');
	while (spacePos != std::string::npos)
	{
		std::string part = args.substr(startPos, spacePos - startPos);
		if (part.find(':') != std::string::npos)
		{
			part.erase(part.find(':'));
			break;
		}
		splitstring.push_back(part);
		startPos = spacePos + 1;
		spacePos = args.find(' ', startPos);
		std::cout << part << std::endl;
	}
	std::string part = args.substr(startPos);
	std::cout << part << std::endl;
	splitstring.push_back(part);
	if (splitstring.size() < 2)
	{
		_sendError(user, ERR_NEEDMOREPARAMS("KICK", user->getNick()));
		return (true);
	}
	Channel *ctarget = _find_channel(splitstring[0]);
	if (!ctarget)
	{
		_sendError(user, ERR_NOSUCHCHANNEL(user->getNick(), splitstring[0]));
		return (true);
	}
	//il faut ajouter le channel admin a la condition
	if (!user->getOpe())
	{
		_sendError(user, ERR_CHANOPRIVSNEEDED(user->getNick(), splitstring[0]));
		return (true);
	}
	if (!ctarget->_findUser(splitstring[1]))
	{
		_sendError(user, ERR_USERNOTINCHANNEL(user->getNick(), splitstring[1], splitstring[0]));
		return (true);	
	}
	if (!ctarget->_findUser(user->getNick()))
	{
		_sendError(user, ERR_NOTONCHANNEL(user->getNick(), splitstring[0]));
		return (true);	
	}
	User *to_ban = _find_user(splitstring[1]);
	ctarget->setBan(to_ban);
	ctarget->_delUser(to_ban);
	if (splitstring.size() > 2)
		_sendError(to_ban, MESSAGE_CMD(user->getNick(), user->getUserName(), user->getHostName(), "KICK", to_ban->getNick(), splitstring[2]));
	else
		_sendError(to_ban, MESSAGE_CMD(user->getNick(), user->getUserName(), user->getHostName(), "KICK", to_ban->getNick(), "You have been banned (sadge)"));
	return (true);
}

	// if (splitstring[1].find(','))
	// {
	// 	size_t comaPos;
	// 	size_t startPosusers = 0;
	// 	comaPos = splitstring[1].find(',');
	// 	while (comaPos != std::string::npos)
	// 	{
	// 		std::string part = splitstring[1].substr(startPosusers, comaPos - startPosusers);
	// 		users_nicks.push_back(part);
	// 		startPosusers = comaPos + 1;
	// 		comaPos = splitstring[1].find(',', startPosusers);
	// 	}
	// 	std::string part = splitstring[1].substr(startPosusers);
	// 	users_nicks.push_back(part);
	// }
