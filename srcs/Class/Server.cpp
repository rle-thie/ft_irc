#include "../../include/Server.hpp"

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
	if (listen(_sd, 30) == -1)
	{
		throw Exception::listen();
	}
	_pollfd.push_back(pollfd());
	_pollfd.back().fd = _sd;
	_pollfd.back().events = POLLIN;
	std::cout << "[IRC SERVER] setup on port " << _port << " at " << std::endl;
}