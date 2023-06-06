#include "../../../include/Irc.hpp"

bool Server::_ping_cmd(User *user, std::string args)
{
	static_cast<void>(args);
	if (args.empty())
		_sendRpl(user, RPL_PONGEMPTY);
	else
		_sendRpl(user, RPL_PONG(args));
	return (true);
}