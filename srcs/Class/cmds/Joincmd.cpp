#include "../../../include/Irc.hpp"

bool	Server::_join_cmd(User *user, std::string args)
{
	std::cout << "[DEBUG] join cmd :" << args << std::endl;
	Channel	*chan = _already_channel_name(args);
	// std::map<std::string, std::string> input = _parseString(args);
	// for (std::map<std::string, std::string>::iterator it = input.begin(); it != input.end(); it++)
	// {
    //     std::cout << "Clé : " << (*it).first << ", Valeur : " << (*it).second << std::endl;
    // }
	if (chan == NULL)
	{
		Channel	*newChannel = new Channel(args);

		newChannel->setUserConnected(user);
		_channels.push_back(newChannel);
		user->addChannel(newChannel);
		newChannel->addop(user);
		_joinRlp(user, newChannel);
	}
	else
	{
		if (chan->_findUser(user->getNick()))
		{
			_sendError(user, ERR_ALREADYJOINED);
			return (false);
		}
		std::cout << "[DEBUG] channel deja existant" << std::endl;
		if (chan->getSizeLimited() && chan->getSizeConnected() >= 2)
		{
			_sendError(user, ERR_CHANNELISFULL(user->getNick(), chan->getName()));
			return (true);
		}
		if (chan->getInviteOnly() == true && user->getInvitedChann(chan) == false)
		{
			_sendError(user, ERR_INVITEONLYCHAN(chan->getName()));
			return (true);
		}
		chan->setUserConnected(user);
		user->addChannel(chan);
		if (user->getOpe() == true)
			chan->addop(user);
		_joinRlp(user, chan);
	}
	
	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		std::cout << (*it)->getName() << std::endl;
	}

	return (true);
}

void	Server::_joinRlp(User *user, Channel *chann)
{
	std::vector<User*>::iterator it;
	for (it = chann->getUsers().begin(); it != chann->getUsers().end(); it++)
	{
		_sendRpl((*it), RPL_JOIN(user->getClient(), chann->getName()));
	}
	if (chann->getTopic() != "")
		_sendRpl(user, RPL_TOPIC(user->getClient(), user->getNick(), chann->getName(), chann->getTopic()));
	_sendRpl(user, RPL_NAMEREPLY(user->getClient(), user->getNick(), chann->getName(), chann->getUsersString()));
	_sendRpl(user, RPL_ENDOFNAMES(user->getClient(), user->getNick(), chann->getName()));
}