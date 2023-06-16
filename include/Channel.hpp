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
		// std::vector<User*>	_ope;
		std::vector<User*>	_opechan;
		std::string			_topic;
		bool				_modeTopicOp;
		bool				_inviteOnly;
		bool				_size_limited;
		int					_maxsize;
		bool				_modeChannelkey;
		std::string			_key;
	
	public :
		Channel(std::string name);
		~Channel();

		//util 
		User*	_findUser(std::string name) const;
		bool	_am_i_banned(User *user);

		// getter
		std::string			getName();
		std::vector<User*> &getUsers();
		std::vector<User*> &getUsersBan();
		std::vector<User*> &getOpeChan();
		int					getSizeConnected();
		std::string			getUsersString();
		std::string			getTopic();
		bool				getModeTopic();
		bool				getSizeLimited();
		bool				getInviteOnly();
		bool				getModeKey();
		std::string			getKey();

		// setter
		void	setName(std::string str);
		void	setUserConnected(User *user);
		void	addop(User *user);
		void	setBan(User *user);
		bool	_delUser(User *user);
		bool	isop(User *user);
		void	setTopic(std::string str);
		void	setModeTopic(bool b);
		void	setSizelimited(bool a);
		void	setInviteOnly(bool b);
		void	setModeKey(bool b);
		void	setKey(std::string key);
		
		void	_addOpeChan(User *user);
		void	_dellOpeChan(User *user);
		bool	_isOpeChan(User *user);
};

#endif
