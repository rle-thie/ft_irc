#ifndef SERVER_HPP
#define SERVER_HPP

#include "Irc.hpp"

class Server;

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
		std::string											_creation_time;

	
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
		int		_disconnectUser(User *user, int ret);
		int		_acceptConnection(User *user, std::pair<std::string, std::string> cmd);

		// send info
		int		_sendError(User *user, std::string err);
		int		_sendRpl(User *user, std::string strtosend);
		int		_sendAll(int fd, const char *buf, size_t len, int flags);
		
		// utils
		bool	_is_auth(User *usr);
		User*	_find_user(std::string nickname);

		//cmds 
		std::map<std::string, bool (Server::*) (User *,std::string)> _cmdmap;
		bool _nick_cmd(User *user, std::string args);
		bool _user_cmd(User *user, std::string args);
		// bool _pass_cmd(User *user, std::string args);
		// bool _join_cmd(User *user, std::string args);
		// bool _oper_cmd(User *user, std::string args);
		// bool _mode_cmd(User *user, std::string args);
		bool _quit_cmd(User *user, std::string args);
		// bool _kick_cmd(User *user, std::string args);
		// bool _privmsg_cmd(User *user, std::string args);
		// bool _invite_cmd(User *user, std::string args);
		// bool _ping_cmd(User *user, std::string args);
		std::string	_current_time();
};

#endif