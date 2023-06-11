#include "../../../include/Irc.hpp"

bool Server::_privmsg_cmd(User *user, std::string args)
{
	std::cout << "[DEBUG] message args : " << args << std::endl;
	std::string target, msg;
	size_t delim;

	delim = args.find(" :");
	if (delim != std::string::npos)
	{
		target = args.substr(0, delim);
		msg = args.substr(delim + 2);
	}
	else
	{
		_sendError(user, ERR_NEEDMOREPARAMS("PRIVMSG", user->getNick()));
		return (true);
	}
	if (target.empty())
	{
		_sendError(user, ERR_NORECIPIENT(user->getNick(), "PRIVMSG"));
		return (true);	
	}
	if (msg.empty())
	{
		_sendError(user, ERR_NOTEXTTOSEND(user->getNick()));
		return (true);
	}
	if(!_find_user(target) && target[0] != '#')
	{
		_sendError(user, ERR_NOSUCHNICK(target, user->getNick()));
		return(true);	
	}

	if (target[0] == '#')
	{
		bool joined = false;
		std::vector<Channel*> chans = user->getChan();
		Channel *ctarget;
		size_t i;
		for (i = 0; i < chans.size() ; i++)
		{
			if(chans[i]->getName() == target)
			{
				joined = true;
				ctarget = chans[i];
				break;
			}
		}
		if (!joined)
		{
			_sendError(user, ERR_NOTONCHANNEL(user->getNick(), target));
			return(true);
		}
		if (_find_channel(target)->_am_i_banned(user->getNick()))
		{
			_sendError(user, ERR_CANNOTSENDTOCHAN(user->getNick(), "target"));
			return (true);
		}
		std::vector<User *>::iterator ite;
		std::vector<User *> targets = ctarget->getUsers();
		for (ite = targets.begin(); ite != targets.end(); ite++)
		{
			if ((*ite) != user && !_find_channel(target)->_am_i_banned((*ite)->getNick()))
			_sendRpl((*ite), MESSAGE(user->getNick(), user->getUserName(), user->getHostName(), target, msg));
		}
		return (true);

	}
	else 
	{
		User *recipient = _find_user(target);
		_sendRpl(recipient, MESSAGE(user->getNick(), user->getUserName(), user->getHostName(), target, msg));
	}

	return (true);
}
