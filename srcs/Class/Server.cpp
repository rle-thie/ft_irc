#include "../../include/Irc.hpp"

// constructor

Server::Server(char *cport, std::string pswd)
{
	_cport = cport;
	_port = atoi(cport);
	_password = pswd;
	_sd = -1;
	_nb_fd = 1;
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
	std::cout << "[IRC SERVER] setup on port " << _port << std::endl;
}

void	Server::start(void)
{
	// throw Exception::err("caca");
	if (_nb_fd == 1)
	{
		std::cout << "wait clients..." << std::endl;
	}
	if (poll(&_pollfd[0], _nb_fd, -1) == -1)
	{
		if (errno != EINTR)
			throw Exception::err("poll error");
		return;
	}
	if (_pollfd[0].revents == POLLIN)
	{
		std::cout << "newuser incomming..." << std::endl;
		_convert_new();
	}
	// std::cout << _pollfd.size() << std::endl;
	std::vector<pollfd>::iterator end_vector = _pollfd.end();
	for (std::vector<pollfd>::iterator iter = _pollfd.begin() + 1; iter != end_vector; iter++)
	{
		// if ((*iter).revents == POLLIN)
			// _trait_requests(*iter);
	}
}

void	Server::_convert_new()
{
	int			new_fd;
	sockaddr_in	new_user;	//addr internet pas n'importe quoi (sockaddr)
	socklen_t	len_sockaddr;

	std::cout << "convert_new()" << std::endl;
	len_sockaddr = sizeof(new_user);
	new_fd = accept(_sd, (sockaddr *)&new_user, &len_sockaddr);
	_user_dict.insert(std::pair<int, User*>(new_fd, new User(new_fd)));
	std::cout << inet_ntoa(new_user.sin_addr) << " !\n" << std::endl;
	_pollfd.push_back(pollfd());
	_pollfd.back().fd = new_fd;
	_pollfd.back().events = POLLIN;
	_nb_fd++;
}

// int	Server::_trait_requests(pollfd pfd)
// {
	// int ret;
	// int lines;
	// int status;

	// if ((ret = _recvAll(pfd)))
	// 	return ret;
	// _recvs.clear();
	// lines = _fillRecvs(std::string(_buff));
	// _buff.clear();
	// for (int i = 0; i < lines; i++) {
	// 	std::cout << DIS_RECV << pfd.fd << DIS_RECVEND(_recvs[i].first, _recvs[i].second) << std::endl;
	// 	if ((status = _manageCmd(pfd, _recvs[i]))) {
	// 		if (status == 2)
	// 			break;
	// 		else if (status == 3)
	// 			_sendError(_users[pfd.fd], ERR_UNKNOWNCOMMAND(_users[pfd.fd]->getClient(), _users[pfd.fd]->getNick(), _recvs[i].first));
	// 		else if (status == 4) {
	// 			stop = true;
	// 			break;
	// 		}
	// 	}
	// }
	// return 0;
// }

Exception::err::err(const char *msg) : _msg(msg)
{
}