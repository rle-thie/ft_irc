#ifndef USER_HPP
#define USER_HPP

#include "Irc.hpp"

class User
{
	private :
		int						_sd;
		std::string				_user_name;
		bool					_first_try;
		std::string				_nick;
		std::string				_host_name;
		bool					_tried_to_auth;
		bool					_auth;
		std::string				_pwd;
		bool					_cap;
		bool					_isope;
		bool					_ischanope;
		std::vector<Channel*>	_channel_joined;
		std::vector<Channel*>	_channel_invited;
	
	public :
		User(int socket_desc, std::string hostname);

		std::vector<Channel*> const	&getChan() const;
		std::string const	getClient() const;
		bool const 			&getFirstTry() const;
		std::string const	getNick() const;
		std::string const	&getPassword() const;
		std::string const	&getUserName() const;
		std::string const	&getHostName() const;
		bool const			&getAuth() const;
		int const			&getUserSd() const;
		bool const			&getCap() const;
		bool const			&getOpe() const;
		bool const			&getChanOpe() const;
		bool				getInvitedChann(Channel *chann);
		bool				isAlreadyInvited(Channel *chann);

		void				setPass(std::string str);
		void				setNick(std::string str);
		void				setUser(std::string str);
		void				setAuth(bool str);
		void				setCap(bool str);
		void				setOpe(bool a);
		void				setChanOpe(bool a);

		void				addInviteChannel(Channel *channel);
		void				addChannel(Channel *channelToAdd);

		~User();

	// private :
	// 	void _convert_new();

};

#endif