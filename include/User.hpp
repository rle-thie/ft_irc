#ifndef USER_HPP
#define USER_HPP

#include "Irc.hpp"

class User
{
	private :
		int			_sd;
		std::string	_pseudo;
		std::string	_addr;
	
	public :
		User(int socket_desc);
		~User();

	// private :
	// 	void _convert_new();
		
};

#endif