#include "../../include/Irc.hpp"

Channel::Channel(std::string name)
{
	_name = name;
	_size_limited = false;
	_maxsize = 2;
	_modeTopicOp = true;
	_inviteOnly = false;
	_modeChannelkey = false;
	_key = "secret";
}

Channel::~Channel()
{
}


std::vector<User*> &Channel::getOpeChan()
{
	return _opechan;
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


void	Channel::_addOpeChan(User *user)
{
	_opechan.push_back(user);
}


void	Channel::_dellOpeChan(User *user)
{
	for (std::vector<User*>::iterator it = _opechan.begin(); it != _opechan.end(); it++)
	{
		if ((*it)->getUserSd() == user->getUserSd())
		{
			_opechan.erase(it);
			return;
		}
	}
	return;
}

bool	Channel::_isOpeChan(User *user)
{
	std::vector<User *>::const_iterator ite = _opechan.begin();
	for (; ite != _opechan.end(); ite++)
	{
		if ((*ite)->getNick() == user->getNick())
			return(true);
	}
	return(false);
}

void	Channel::addop(User *user)
{
	_opechan.push_back(user);
}

void	Channel::setSizelimited(bool a)
{
	_size_limited = a;
}

bool	Channel::_delUser(User *user)
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
	std::vector<User*>::iterator it = _opechan.begin();
	for (; it != _opechan.end(); it++)
	{
		if ((*it) == user)
			return (true); 
	}
	return (false);
}

std::string	Channel::getTopic()
{
	return (_topic);
}

void	Channel::setTopic(std::string str)
{
	_topic = str;
}

bool	Channel::getModeTopic()
{
	return (_modeTopicOp);
}

void	Channel::setModeTopic(bool b)
{
	_modeTopicOp = b;
}

bool	Channel::getInviteOnly()
{
	return (_inviteOnly);
}

void	Channel::setInviteOnly(bool b)
{
	_inviteOnly = b;
}

void	Channel::setModeKey(bool b)
{
	_modeChannelkey = b;
}

bool	Channel::getModeKey()
{
	return (_modeChannelkey);
}

std::string	Channel::getKey()
{
	return (_key);
}

void	Channel::setKey(std::string str)
{
	_key = str;
}