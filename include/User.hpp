#ifndef USER_HPP
#define USER_HPP

#include "Irc.hpp"

class User
{
	private :
		int			_sd;
		std::string	_user_name;
		bool		_first_try;
		std::string	_nick;
		std::string	_host_name;
		bool		_tried_to_auth;
		bool		_auth;
	
	public :
		User(int socket_desc);
		std::string const	getClient() const;
		bool const 			&getFirstTry() const;
		std::string const	getNick() const;
		std::string const	&getUserName() const;
		std::string const	&getHostName() const;
		bool const			&getTriedToAuth() const;
		bool const			&getAuth() const;
		int const			&getUserSd() const;

		~User();

	// private :
	// 	void _convert_new();

};

#endif