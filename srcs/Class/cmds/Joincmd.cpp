#include "../../../include/Irc.hpp"

bool	Server::_join_cmd(User *user, std::string args)
{
	std::cout << "[DEBUG] join cmd :" << args << std::endl;
	Channel	*chan = _already_channel_name(args);
	if (chan == NULL)
	{
		Channel	*NewChannel = new Channel(args);

		NewChannel->setUserConnected(user);
		_channels.push_back(NewChannel);
		user->addChannel(NewChannel);
		_joinRlp(user, NewChannel);
	}
	else
	{
		std::cout << "channel deja existant" << std::endl;
		if (chan->getSizeLimited() && chan->getSizeConnected() >= 5)
		{
			_sendError(user, ERR_CHANNELISFULL(user->getNick(), chan->getName()));
			return (true);
		}
		chan->setUserConnected(user);
		user->addChannel(chan);
		_joinRlp(user, chan);
		// _sendRpl(user, );
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
	// if (topic ?)
	// 	send rpl topic
	_sendRpl(user, RPL_NAMEREPLY(user->getClient(), user->getNick(), chann->getName(), chann->getUsersString()));
	_sendRpl(user, RPL_ENDOFNAMES(user->getClient(), user->getNick(), chann->getName()));
}