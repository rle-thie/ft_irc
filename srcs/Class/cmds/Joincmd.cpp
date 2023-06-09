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
		
	}
	else
	{
		std::cout << "channel deja existant" << std::endl;
		chan->setUserConnected(user);
		user->addChannel(chan);
		// _sendRpl(user, );
	}
	
	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		std::cout << (*it)->getName() << std::endl;
	}

	return (true);
}