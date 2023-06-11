#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Irc.hpp"

class User;

class Channel
{
	private :
		std::string			_name;
		std::vector<User*>	_connected;
		std::vector<User*>	_ban_list;
		// std::string			_mode;
	
	public :
		Channel(std::string name);
		~Channel();

		// getter
		std::string	getName();
		std::vector<User*> &getUsers();
		std::vector<User*> &getUsersBan();
		int			getSizeConnected();

		// setter
		void	setName(std::string str);
		void	setUserConnected(User *user);
		void	setBan(User *user);
		void	_delUser(User *user);

	// private :
	// 	void _convert_new();

};

#endif