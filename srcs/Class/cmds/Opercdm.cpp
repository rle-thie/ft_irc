#include "../../../include/Irc.hpp"

bool Server::_oper_cmd(User *user, std::string args)
{
	std::string nick, pwd;
	size_t delim = args.find(' ');

	if (delim != std::string::npos)
	{
		nick = args.substr(0, delim);
		pwd = args.substr(delim + 1);
	}
	if (args.empty() || delim == std::string::npos)
	{
		_sendError(user, ERR_NEEDMOREPARAMS("OPER", user->getNick()));
		return (true);
	}
	if (pwd != _opepass)
	{
		_sendError(user, ERR_PASSWDMISMATCH(user->getNick()));
		return (true);
	}
	user->setOpe(true);
	_sendRpl(user, RPL_YOUREOPER(user->getNick()));
	return (true);
}
