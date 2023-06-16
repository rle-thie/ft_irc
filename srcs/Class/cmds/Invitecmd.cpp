#include "../../../include/Irc.hpp"

bool Server::_invite_cmd(User *user, std::string args)
{
	std::cout << "[DEBUG] invite cmd " << args << std::endl;
	std::string myString = args;
    std::string::size_type spacePos = myString.find(" ");

    if (spacePos != std::string::npos)
	{
        std::string usernick = myString.substr(0, spacePos);
        std::string chann_name = myString.substr(spacePos + 1);

		std::cout << usernick << "--" << chann_name << std::endl;
		Channel *chann = _already_channel_name(chann_name);
		User	*invite_user = _find_user(usernick);
		if (chann == NULL)
		{
			_sendError(user, ERR_NOSUCHCHANNEL(user->getNick(), chann_name));
			return (false);
		}
		if (invite_user == NULL)
		{
			_sendError(user, ERR_NOSUCHNICK(user->getNick(), usernick));
			return (false);
		}
		if (chann->_findUser(user->getNick()) == NULL)
		{
			_sendError(user, ERR_NOTONCHANNEL(user->getNick(), chann->getName()));
			return (false);
		}
		if (chann->getInviteOnly() == false)
		{
			_sendError(user, ERR_NOTINVITEMODE);
			return (false);
		}
		if (chann->_findUser(usernick) != NULL)
		{
			_sendError(user, ERR_USERONCHANNEL(invite_user->getNick(), chann->getName()));
			return (false);
		}
		if (invite_user->isAlreadyInvited(chann) == true)
		{
			_sendError(user, ERR_USERALREADYINVITE(invite_user->getNick(), chann->getName()));
			return (false);
		}
		invite_user->addInviteChannel(chann);
		_sendRpl(user, RPL_INVITE(invite_user->getNick(), chann->getName()));
		_sendRpl(invite_user, RPL_INVITED(user->getNick(), chann->getName()));
	}
	else
	{
		_sendError(user, ERR_NEEDMOREPARAMS(user->getNick(), args));
		return (false);
    }
	return (false);
}
