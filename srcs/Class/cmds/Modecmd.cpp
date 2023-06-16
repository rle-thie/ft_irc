#include "../../../include/Irc.hpp"

bool	Server::_mode_cmd(User *user, std::string args)
{
	std::vector<std::string> params;
	size_t spacePos;
	size_t startPos = 0;


	spacePos = args.find(' ');
	while (spacePos != std::string::npos)
	{
		std::string part = args.substr(startPos, spacePos - startPos);
		if (part.find(':') != std::string::npos)
			break;
		params.push_back(part);
		startPos = spacePos + 1;
		spacePos = args.find(' ', startPos);
	}
	std::string part = args.substr(startPos);
	params.push_back(part);
	std::cout << "[DEBUG] mode cmd :" << args << std::endl;
	if (params.size() < 2)
	{
		_sendError(user, ERR_NEEDMOREPARAMS("MODE", user->getNick()));
		return (true);
	}
	if (params[0][0] == '#')
	{
		Channel *target = _find_channel(params[0]);
		if(!target)
			return (true);
		if (target->_isOpeChan(user))
		if (!(user->getOpe() || target->_isOpeChan(user)))
		{
			_sendError(user, ERR_CHANOPRIVSNEEDED(params[0]));
			return (true);
		}
		if (params[1].size() != 2 || (params[1][0] != '+' && params[1][0] != '-'))
		{
			_sendError(user, ERR_UMODEUNKNOWNFLAG(user->getNick()));
			return (true);
		}
		char mode = params[1][1]; 
		switch (mode)
		{
		case 'i':
			if (params[1][0] == '+')
				target->setInviteOnly(true);
			else 
				target->setInviteOnly(false);
			break;
		case 't':
			if (params[1][0] == '+')
				target->setModeTopic(true);
			else 
				target->setModeTopic(false);
			break;
		case 'k':
			if (params[1][0] == '+')
				target->setModeKey(true);
			else 
				target->setModeKey(false);
			break;
		case 'l':
			if (params[1][0] == '+')
				target->setSizelimited(true);
			else 
				target->setSizelimited(false);
			break;
		case 'o':
		{
			if (params.size() != 3)
			{
				_sendError(user, ERR_NEEDMOREPARAMS("MODE", user->getNick()));
				return (true);
			}
			User *targetuser = target->_findUser(params[2]);
			if (!targetuser)
			{
				_sendError(user, ERR_USERNOTINCHANNEL(user->getNick(), params[0], params[2]));
				return (true);			
			}
			if (params[1][0] == '+' && !target->_isOpeChan(targetuser))
				target->_addOpeChan(targetuser);
			else if (params[1][0] == '-' && target->_isOpeChan(targetuser))
				target->_dellOpeChan(targetuser);
			else 
				return (true);
			break;
		}
		default:
			{
				_sendError(user, ERR_UMODEUNKNOWNFLAG(user->getNick()));
				return (true);
			}
			break;
		}
	}
	else
	{
		_sendError(user, ERR_UMODEUNKNOWNFLAG(user->getNick()));
		return (true);
	}	
	return(true);

}
