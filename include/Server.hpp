#ifndef SERVER_HPP
#define SERVER_HPP

#include "Irc.hpp"

typedef int (Server::*commands)(User*, std::string);

class Server
{
	private :
		char												*_cport;
		int													_port;
		std::string											_password;
		int													_sd;
		std::vector<pollfd> 								_pollfd;
		int													_nb_fd;
		std::map<int, User*>								_user_dict;
		std::string											_buff;
		std::vector<std::pair<std::string, std::string> >	_recvs;
		std::map<const std::string, commands>				_commands;
	
	public :
		Server(char *cport, std::string pswd);
		~Server();
		void	clear();
		void	init();
		void	start();
	
	private :
		void	_convert_new();
		int		_trait_requests(pollfd pfd);
		size_t	_recvAll(pollfd pollfd);
		int		_fillRecvs(std::string buff);
		int		_manageCmd(pollfd pfd, std::pair<std::string, std::string> cmd);
		int		_sendError(User *user, std::string err);
		int		_sendAll(int fd, const char *buf, size_t len, int flags);
		int		_disconnectUser(User *user, int ret);
		int		_acceptConnection(User *user, std::pair<std::string, std::string> cmd);
};

#endif