#ifndef SERVER_HPP
#define SERVER_HPP

#include "Irc.hpp"

class Server
{
	private :
		int			_port;
		std::string	_password;
	public :
		Server(int port, std::string pswd);
		~Server();
		
};

#endif