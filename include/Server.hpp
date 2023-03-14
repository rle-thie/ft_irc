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
		std::map<int, User*>	_user_dict;
	
	public :
		Server(char *cport, std::string pswd);
		~Server();
		void	init();
		void	start();
	
	private :
		void	_convert_new();
		int		_trait_requests(pollfd pfd);
		
};

#endif