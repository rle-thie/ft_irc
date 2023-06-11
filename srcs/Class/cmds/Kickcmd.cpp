#include "../../../include/Irc.hpp"

bool Server::_kick_cmd(User *user, std::string args)
{
	std::vector<std::string> splitstring;
	size_t spacePos;
	size_t startPos = 0;
	int i = 0;

	spacePos = args.find(' ');
	while (spacePos != std::string::npos)
	{
		std::string part = args.substr(startPos, spacePos - startPos);
		splitstring.push_back(part);
		startPos = spacePos + 1;
		spacePos = args.find(' ', startPos);
	}
	std::string part = args.substr(startPos);
	splitstring.push_back(part);
	return (true);
}