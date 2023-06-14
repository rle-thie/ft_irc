#include "../../../include/Irc.hpp"

bool	Server::_join_cmd(User *user, std::string args)
{
	std::cout << "[DEBUG] join cmd :" << args << std::endl;


    std::vector<std::pair<std::string, std::string> > v = strtovec(args);
	std::vector<std::pair<std::string, std::string> >::iterator it = v.begin();
	for(; it != v.end(); it++)
	{
		std::cout << (*it).first << "--" << (*it).second << std::endl;
		Channel	*chan = _already_channel_name((*it).first);
		std::string key = (*it).second;
		if (key == "x")
			key = "";
		if (chan == NULL)
		{
			Channel	*newChannel = new Channel((*it).first);

			newChannel->setUserConnected(user);
			_channels.push_back(newChannel);
			user->addChannel(newChannel);
			newChannel->addop(user);
			if (key != "")
				newChannel->setKey(key);
			std::cout << "[DEBUG] create new channel..." << std::endl;
			_joinRlp(user, newChannel);
		}
		else
		{
			std::cout << "[DEBUG] channel deja existant" << std::endl;
			if (chan->_findUser(user->getNick()))
			{
				_sendError(user, ERR_ALREADYJOINED);
				// return (false);
				continue;
			}
			if (chan->getSizeLimited() && chan->getSizeConnected() >= 2)
			{
				_sendError(user, ERR_CHANNELISFULL(user->getNick(), chan->getName()));
				// return (true);
				continue;
			}
			std::cout << "tttttttttttt" << std::endl;
			if (chan->getInviteOnly() == true && user->getInvitedChann(chan) == false)
			{
				_sendError(user, ERR_INVITEONLYCHAN(chan->getName()));
				// return (true);
				continue;
			}
			if (chan->getModeKey() == true && key == "")
			{
				_sendError(user, ERR_BADCHANNELKEY(chan->getName()));
				continue;
			}
			if (chan->getModeKey() == true && key != chan->getKey())
			{
				_sendError(user, ERR_INVALIDKEY(chan->getName()));
				continue;
			}
			chan->setUserConnected(user);
			user->addChannel(chan);
			if (user->getOpe() == true)
				chan->addop(user);
			_joinRlp(user, chan);
		}
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

std::vector<std::pair<std::string, std::string> > Server::strtovec(std::string buff)
{
	std::string keys;
	std::string tmp_key;
	std::string channels;
	std::string tmp_channel;
	size_t space = buff.find(' ');
	std::vector<std::pair<std::string, std::string> > args;

	if (space != buff.npos) {
		channels = std::string(buff.begin(), buff.begin() + space);
		keys = std::string(buff.begin() + space + 1, buff.end());
	}
	else
		channels = std::string(buff.begin(), buff.end());
	std::istringstream channels_buffstream(channels);
	std::istringstream keys_buffstream(keys);
	while(std::getline(channels_buffstream, tmp_channel, ',')) {
		if (space != buff.npos)
			std::getline(keys_buffstream, tmp_key, ',');
		args.push_back(std::make_pair(tmp_channel, tmp_key));
	}
	return args;
}