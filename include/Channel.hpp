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

		//util 
		User*	_findUser(std::string name) const;
		bool	_am_i_banned(std::string name);

		// getter
		std::string			getName();
		std::vector<User*> &getUsers();
		std::vector<User*> &getUsersBan();
		int					getSizeConnected();
		std::string			getUsersString();

		// setter
		void	setName(std::string str);
		void	setUserConnected(User *user);
		void	setBan(User *user);
		void	_delUser(User *user);

	// private :
	// 	void _convert_new();

};

#endif