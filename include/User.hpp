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
		bool		_cap;
		bool		_tried_to_auth;
		bool		_auth;
		bool		_cap;
	
	public :
		User(int socket_desc);
		std::string const	getClient() const;
		bool const 			&getFirstTry() const;
		std::string const	getNick() const;
		std::string const	&getUserName() const;
		std::string const	&getHostName() const;
		bool const			&getCap() const;
		bool const			&getTriedToAuth() const;
		bool const			&getAuth() const;
		int const			&getUserSd() const;

		void				setCap(bool value);
		~User();

	// private :
	// 	void _convert_new();

};

#endif