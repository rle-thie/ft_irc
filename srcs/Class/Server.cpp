/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevy <ldevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:57:16 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/07 15:01:23 by ldevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/Irc.hpp"

extern bool run;

// constructor

Server::Server(char *cport, std::string pswd)
{
	_cport = cport;
	_port = atoi(cport);
	_password = pswd;
	_sd = -1;
	_nb_fd = 1;
	_cmdmap["NICK"] = &Server::_nick_cmd;
	_cmdmap["USER"] = &Server::_user_cmd;
	_opepass = "secret";
	// _cmdmap["PASS"] = &Server::_pass_cmd;
	// _cmdmap["JOIN"] = &Server::_join_cmd;
	_cmdmap["OPER"] = &Server::_oper_cmd;
	// _cmdmap["MODE"] = &Server::_mode_cmd;
	_cmdmap["QUIT"] = &Server::_quit_cmd;
	// _cmdmap["KICK"] = &Server::_kick_cmd;
	// _cmdmap["PRIVMSG"] = &Server::_privmsg_cmd;
	// _cmdmap["INVITE"] = &Server::_invite_cmd;
	_cmdmap["PING"] = &Server::_ping_cmd;
	_creation_time = _current_time();
}

Server::~Server()
{
}

// https://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_lib_ref/a/addrinfo.html
// http://manpagesfr.free.fr/man/man3/getaddrinfo.3.html
void	Server::init(void)
{
	addrinfo	hints;
	addrinfo	*info_server = NULL;
	addrinfo	*tmp = NULL;
	int			optval = 1;

	tmp=tmp;

	memset(&hints, 0, sizeof(hints));
	// La valeur AF_UNSPEC indique que getaddrinfo() doit renvoyer les adresses de socket de n'importe quelle famille d'adresses (par exemple, IPv4 ou IPv6) pouvant être utilisées avec node et service.
	hints.ai_family = AF_UNSPEC;
	// Ce champ indique le type préféré de socket, par exemple SOCK_STREAM ou SOCK_DGRAM. Mettre 0 dans ce champ indique que getaddrinfo() peut renvoyer n'importe quel type d'adresses de socket.
	hints.ai_socktype = SOCK_STREAM;
	// Si l'attribut AI_PASSIVE est indiqué dans hints.ai_flags, et si node est NULL, les adresses de socket renvoyées seront pertinentes pour lier (bind(2)) un socket qui acceptera (accept(2)) les connexions
	hints.ai_flags = AI_PASSIVE;
	
	if (getaddrinfo(NULL, _cport, &hints, &info_server))
	{
		throw Exception::getaddrinfo();
	}
	for (tmp = info_server; tmp; tmp = tmp->ai_next)
	{
		// http://manpagesfr.free.fr/man/man2/socket.2.html
		if ((_sd = socket(info_server->ai_family, info_server->ai_socktype, info_server->ai_protocol)) == -1)
			continue;
		// http://manpagesfr.free.fr/man/man2/getsockopt.2.html
		setsockopt(_sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));
		fcntl(_sd, F_SETFL, O_NONBLOCK); // set flag
		// affecte l'adresse spécifiée dans addr à la socket référencée par le descripteur de fichier
		if (bind(_sd, info_server->ai_addr, info_server->ai_addrlen))
		{
			close(_sd);
			continue;
		}
		break;
	}
	if (tmp == NULL)
	{
		freeaddrinfo(info_server);
		throw Exception::nobind();
	}
	freeaddrinfo(info_server);
	// 30 = nbrs de connexion en attente
	if (listen(_sd, 30) == -1)
	{
		throw Exception::listen();
	}
	_pollfd.push_back(pollfd());
	_pollfd.back().fd = _sd;
	_pollfd.back().events = POLLIN;
	// std::cout << _pollfd.back().events << std::endl;
	// std::cout << _pollfd.back().fd << std::endl;
	// std::cout << _pollfd.back().revents << std::endl;
	std::cout << GREEN GRAS<< "[IRC SERVER] setup on port " << _port << RESET << std::endl;
}

void	Server::start(void)
{
	// throw Exception::err("caca");
	if (_nb_fd == 1)
	{
		std::cout << BLUE << "wait clients..." << RESET << std::endl;
	}
	if (poll(&_pollfd[0], _nb_fd, -1) == -1)
	{
		if (errno != EINTR)
			throw Exception::err("poll error");
		return;
	}
	if (_pollfd[0].revents == POLLIN)
	{
		// std::cout << "newuser incomming..." << std::endl;
		_convert_new();
	}
	// std::cout << _pollfd.size() << std::endl;
	std::vector<pollfd>::iterator end_vector = _pollfd.end();
	for (std::vector<pollfd>::iterator iter = _pollfd.begin() + 1; iter != end_vector; iter++)
	{
		if ((*iter).revents == POLLIN)
			_trait_requests(*iter);
	}
}

int Server::_disconnectUser(User *user, int ret)
{
	std::string disconnection(" has been disconnected!");
	std::string delimiter("================================");

	// https://ircv3.net/specs/extensions/capability-negotiation.html#:~:text=Capability%20Negotiation%20means%20that%20client,new%20features%20and%20vice%2Dversa.
	// if !cap
	// 	error cap
	// if (user->getTriedToAuth() && !user->getAuth())
		// password incorrecte
	// if (user->getTriedToAuth() && user->getNick() == "")
		// no nick error
	// if (user->getTriedToAuth() && user->getUserName() == "")
		// error no user info
	if (user->getAuth())
	{
		disconnection = " left !";
		delimiter = "==============================";
	}
	// else if (!user->getTriedToAuth())
		// error no password
	std::cout << RED << "=========" << delimiter << std::endl;
	std::cout << "[IRC SERVER] User " << user->getUserSd() << disconnection << std::endl;
	std::cout << "=========" << delimiter << RESET << std::endl;
	std::vector<pollfd>::iterator it;
	for (it = _pollfd.begin() + 1; it->fd != user->getUserSd(); it++)
		;
		
	// usr->removeFromAllChannel();
	// _delEmptyChans();

	_pollfd.erase(it);
	_user_dict.erase(user->getUserSd());
	_recvs.clear();
	_nb_fd--;
	close(user->getUserSd());
	delete user;
	return ret;
}

// ajoute les nouvelles connections a la liste _user_dict
void	Server::_convert_new()
{
	int			new_fd;
	sockaddr_in	new_user;	//addr internet pas n'importe quoi (sockaddr)
	socklen_t	len_sockaddr;

	// std::cout << "convert_new()" << std::endl;
	len_sockaddr = sizeof(new_user);
	new_fd = accept(_sd, (sockaddr *)&new_user, &len_sockaddr);
	_user_dict.insert(std::pair<int, User*>(new_fd, new User(new_fd, inet_ntoa(new_user.sin_addr))));
	// inet_ntoa() converti en une adresse ip normal
	// std::cout << inet_ntoa(new_user.sin_addr) << " !\n" << std::endl;
	_pollfd.push_back(pollfd());
	_pollfd.back().fd = new_fd;
	_pollfd.back().events = POLLIN;
	_nb_fd++;
	std::cout << GRAS "[IRC SERVER] " RESET GREEN << "User" << new_fd << " is comming" RESET << std::endl; 
}

int	Server::_trait_requests(pollfd pfd)
{
	int ret;
	int lines;
	// int status;

	if ((ret = _recvAll(pfd)))
		return ret;
	_recvs.clear();
	lines = _fillRecvs(std::string(_buff));
	// std::cout << "[DEBUG] total ligne:" << lines << ", packet brut recv:'" << _buff << "'" << std::endl;
	_buff.clear();
	// for (int i = 0; i < lines; i++)
	// {
	// 	std::cout << "[DEBUG] ligne:" << i << "_first:" << _recvs[i].first << "_seconde:" << _recvs[i].second << std::endl;
	// }
	for (int i = 0; i < lines; i++)
	{
		std::cout << DIS_RECV << pfd.fd << DIS_RECVEND(_recvs[i].first, _recvs[i].second) << std::endl;
		// si manageCmd renvoie 1 = on stop l'execution des cmd en attente parce que erreur donc plus de user et donc ca segfault
		if (_manageCmd(pfd, _recvs[i]) == 1)
			break;
	}
	return 0;
}

size_t Server::_recvAll(pollfd pollfd) {
	char buffer[BUFFER_SIZE + 1];
	int size;

	while (1) {
		memset(buffer, 0, BUFFER_SIZE + 1);
		// http://manpagesfr.free.fr/man/man2/recv.2.html
		// L'appel recv() est normalement utilisé sur une socket connectée et est équivalent à recvfrom() avec un paramètre from NULL.
		// Ces trois routines renvoient la longueur du message si elles réussissent. Si un message est trop long pour tenir dans le tampon, les octets supplémentaires peuvent être abandonnés suivant le type de socket utilisé.
		if ((size = recv(pollfd.fd, buffer, BUFFER_SIZE, 0)) == -1)
			return -1;
		if (size == 0)
		{
			// std::cout << "disconnect user... inprogress" << std::endl;
			std::cout << "[DEBUG] size = 0 ---> disconnect" << std::endl;
			return _disconnectUser(_user_dict[pollfd.fd], 0);
			return 1;
		}
		buffer[size] = 0;
		_buff += buffer;
		if (_buff.find('\n') != _buff.npos)
			break;
	}
	return 0;
}

void Server::clear()
{
	_recvs.clear();
	for (std::map<int, User*>::iterator it = _user_dict.begin(); it != _user_dict.end(); it++)
		delete (*it).second;
	_user_dict.clear();
	for (std::vector<pollfd>::iterator it = _pollfd.begin(); it != _pollfd.end(); it++)
		close(it->fd);
	_pollfd.clear();
}

int Server::_fillRecvs(std::string buff)
{
	size_t space_pos;
	size_t backr_pos;
	std::string::iterator begin;
	std::string::iterator space;
	std::string::iterator backr;
	int lines = std::count(buff.begin(), buff.end(), '\n');

	for (int i = 0; i < lines; i++) {
		begin = buff.begin();
		space_pos = buff.find(' ');
		backr_pos = buff.find('\r');
		space = begin + space_pos;
		backr = begin + backr_pos;
		if (backr_pos == buff.npos && space_pos == buff.npos)
			_recvs.push_back(std::make_pair(std::string(begin, buff.end() - 1), std::string()));
		else if (space_pos == buff.npos)
			_recvs.push_back(std::make_pair(std::string(begin, buff.end() - 2), std::string()));
		else {
			if (backr_pos == buff.npos)
				_recvs.push_back(std::make_pair(std::string(begin, space), std::string(space + 1, buff.end() - 1)));
			else
				_recvs.push_back(std::make_pair(std::string(begin, space), std::string(space + 1, backr)));
		}
		buff.erase(begin, backr + 2);
	}
	return lines;
}

int Server::_acceptConnection(User *user, std::pair<std::string, std::string> cmd)
{
	user = user;
	cmd = cmd;
	bool ret = true;
	
	std::map<std::string, bool (Server::*)(User *, std::string)>::iterator iter;
	for (iter = _cmdmap.begin(); iter != _cmdmap.end(); iter++)
	{
		// on exec si la cmd est trouvée
		if (cmd.first == iter->first)
		{
        	ret = (this->*(iter->second))(user, cmd.second);
			return (ret);
		}
		else if (cmd.first == "CAP")
			return true;
		// si on ne trouve pas la cmd on envoie uknowncmd et si c'est un cap on ignore
	}
	if (iter == _cmdmap.end())
		_sendError(user, ERR_UNKNOWNCOMMAND(user->getNick(), cmd.first));
	return true;
}

Exception::err::err(const char *msg) : _msg(msg)
{
}
