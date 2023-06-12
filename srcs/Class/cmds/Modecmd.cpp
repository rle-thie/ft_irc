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
	if (params.size() != 2)
	{
		_sendError(user, ERR_NEEDMOREPARAMS("MODE", user->getNick()));
		return (true);
	}
	//chan mode
	if (params[0][0] == '#')
	{
		Channel *target = _find_channel(params[0]);
		if(!target)
			return (true);
		if (params[1].size() != 2 || !params[1][0] == '+' || !params[1][0] == '-')
		{
			_sendError(user, ERR_UMODEUNKNOWNFLAG(user->getNick()));
			return (true);
		}
		switch (params[1][1])
		{
		case 'i':
			if (params[1][0] == '+')
				// target._setInvite(true);
			else 
				// target._setInvite(false);
			break;
		case 't':
			/* code */
			break;
		case 'k':
			/* code */
			break;
		case 'l':
			/* code */
			break;	
		default:
			{
				_sendError(user, ERR_UMODEUNKNOWNFLAG(user->getNick()));
				return (true);
			}
			break;
		}
	}
	//mode sur user
	else if (params[1] == "+o" || params[1] == "-o")
	{

	}
	else
	{
		_sendError(user, ERR_UMODEUNKNOWNFLAG(user->getNick()));
		return (true);
	}
	
	return(true);

}
