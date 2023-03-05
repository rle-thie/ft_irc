#ifndef SERVER_HPP
#define SERVER_HPP

#include "Irc.hpp"

class Server
{
	private :
		char					*_cport;
		int						_port;
		std::string				_password;
		int						_sd;
		std::vector<pollfd> 	_pollfd;
		int						_nb_fd;
	
	public :
		Server(char *cport, std::string pswd);
		~Server();
		void	init();
		// start();
		
};

#endif