#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Irc.hpp"

class User;

class Channel
{
	private :
		std::string			_name;
		std::vector<User*>	_connected;
		// std::string			_mode;
	
	public :
		Channel(std::string name);
		~Channel();

		// getter
		std::string	getName();
		int			getSizeConnected();

		// setter
		void	setName(std::string str);
		void	setUserConnected(User *user);

		void	_delUser(User *user);

	// private :
	// 	void _convert_new();

};

#endif