#include "../../include/Irc.hpp"

Channel::Channel(std::string name)
{
	_name = name;
}

Channel::~Channel()
{
}

std::string	Channel::getName()
{
	return (_name);
}

int	Channel::getSizeConnected()
{
	return (_connected.size());
}

void	Channel::setName(std::string str)
{
	_name = str;
}

void	Channel::setUserConnected(User *user)
{
	_connected.push_back(user);
}

void	Channel::_delUser(User *user)
{
	for (std::vector<User*>::iterator it = _connected.begin(); it != _connected.end(); it++)
	{
		if ((*it)->getUserSd() == user->getUserSd())
		{
			_connected.erase(it);
			return ;
		}
	}
}
