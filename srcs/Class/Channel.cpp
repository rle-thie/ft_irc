#include "../../include/Irc.hpp"

Channel::Channel(std::string name)
{
	_name = name;
	_size_limited = false;
	_maxsize = 2;
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


bool	Channel::getSizeLimited()
{
	return _size_limited;
}

std::vector<User*> &Channel::getUsers()
{
	return _connected;
}

std::vector<User*> &Channel::getUsersBan()
{
	return _ban_list;
}

void	Channel::setName(std::string str)
{
	_name = str;
}

void	Channel::setUserConnected(User *user)
{
	_connected.push_back(user);
}

void	Channel::setBan(User *user)
{
	_ban_list.push_back(user);
}

void	Channel::setSizelimited(bool a)
{
	_size_limited = a;
}

void	Channel::addop(User *user)
{
	_ope.push_back(user);
}

void	Channel::_delUser(User *user)
{
	for (std::vector<User*>::iterator it = _connected.begin(); it != _connected.end(); it++)
	{
		if ((*it)->getUserSd() == user->getUserSd())
		{
			_connected.erase(it);
			return (true);
		}
	}
	return (false);
}

User* Channel::_findUser(std::string name) const
{
	std::vector<User *>::const_iterator ite = _connected.begin();
	for (; ite != _connected.end(); ite++)
	{
		if ((*ite)->getNick() == name)
			return(*ite);
	}
	return(NULL);
}


bool Channel::_am_i_banned(std::string name)
{
	std::vector<User *>::const_iterator ite = _ban_list.begin();
	for (; ite != _ban_list.end(); ite++)
	{
		if ((*ite)->getNick() == name)
			return(true);
	}
	return(false);
}

std::string	Channel::getUsersString()
{
	std::string	ret;
	for (std::vector<User*>::iterator it = _connected.begin(); it != _connected.end(); it++)
	{
		if (it != _connected.begin())
		{
			ret = ret + " ";
		}
		if (isop((*it)) == true)
			ret = ret + "@";
		ret = ret + (*it)->getNick();
	}
	return (ret);
}

bool	Channel::isop(User *user)
{
	std::vector<User*>::iterator it = _ope.begin();
	for (; it != _ope.end(); it++)
	{
		if ((*it) == user)
			return (true); 
	}
	return (false);
}
