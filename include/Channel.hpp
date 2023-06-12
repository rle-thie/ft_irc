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
		std::string			_topic;
		bool				_modeTopicOp;
		bool				_inviteOnly;
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
		std::string			getTopic();
		bool				getModeTopic();

		// setter
		void	setName(std::string str);
		void	setUserConnected(User *user);
		void	addop(User *user);
		void	setBan(User *user);
		bool	_delUser(User *user);
		bool	isop(User *user);
		void	setTopic(std::string str);
		void	setModeTopic(bool b);

	// private :
	// 	void _convert_new();

};

#endif