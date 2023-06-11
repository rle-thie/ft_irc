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
		std::vector<User*>	_ope;
		// std::string			_mode;
	
	public :
		Channel(std::string name);
		~Channel();

		// getter
		std::string			getName();
		std::vector<User*> &getUsers();
		std::vector<User*> &getUsersBan();
		int					getSizeConnected();
		std::string			getUsersString();

		// setter
		void	setName(std::string str);
		void	setUserConnected(User *user);
		void	addop(User *user);
		void	setBan(User *user);
		bool	_delUser(User *user);
		bool	isop(User *user);

	// private :
	// 	void _convert_new();

};

#endif