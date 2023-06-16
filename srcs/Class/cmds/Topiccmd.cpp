#include "../../../include/Irc.hpp"

bool Server::_topic_cmd(User *user, std::string args)
{
	std::cout << "[DEBUG] topic cmd " << args << std::endl;
	// user = user;

	std::string myString = args;
    std::string::size_type spacePos = myString.find(" :");

    if (spacePos != std::string::npos)
	{
        std::string chann_name = myString.substr(0, spacePos);
        std::string topic = myString.substr(spacePos + 2);
		Channel *chann = _already_channel_name(chann_name);
		if (chann == NULL)
		{
			_sendError(user, ERR_NOSUCHCHANNEL(user->getNick(), chann_name));
			return (false);
		}
		if (chann->_findUser(user->getNick()) == NULL)
		{
			_sendError(user, ERR_NOTONCHANNEL(user->getNick(), chann->getName()));
			return (false);
		}
		if (chann->getModeTopic() == true && chann->isop(user) == false)
		{
			_sendError(user, ERR_CHANOPRIVSNEEDED(chann->getName()));
			return (false);
		}
		std::string::size_type space = topic.find(" ");
		chann_name = topic.substr(0, spacePos);
        std::string topicc = topic.substr(space + 1);
		std::cout << topicc << std::endl;
		chann->setTopic(topicc);
		_sendTopic(user, chann);
		// _sendRpl(user, RPL_TOPIC(user->getClient(), user->getNick(), chann->getName(), chann->getTopic()));
	}
	else
	{
		_sendError(user, ERR_NEEDMOREPARAMS(user->getNick(), args));
		return (false);
    }
	return (true);
}

void	Server::_sendTopic(User *user, Channel *chann)
{
	std::vector<User*>::iterator it;
	for (it = chann->getUsers().begin(); it != chann->getUsers().end(); it++)
	{
		_sendRpl((*it), RPL_TOPIC(user->getClient(), user->getNick(), chann->getName(), chann->getTopic()));
	}
}
