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
	std::cout << _pollfd.size() << std::endl;
	std::vector<pollfd>::iterator end_vector = _pollfd.end();
	for (std::vector<pollfd>::iterator iter = _pollfd.begin() + 1; iter != end_vector; iter++)
	{
		if ((*iter).revents == POLLIN)
			_trait_requests(*iter);
	}
}

// ajoute les nouvelles connections a la liste _user_dict
void	Server::_convert_new()
{
	int			new_fd;
	sockaddr_in	new_user;	//addr internet pas n'importe quoi (sockaddr)
	socklen_t	len_sockaddr;

	std::cout << "convert_new()" << std::endl;
	len_sockaddr = sizeof(new_user);
	new_fd = accept(_sd, (sockaddr *)&new_user, &len_sockaddr);
	_user_dict.insert(std::pair<int, User*>(new_fd, new User(new_fd)));
	// inet_ntoa() converti en une adresse ip normal
	std::cout << inet_ntoa(new_user.sin_addr) << " !\n" << std::endl;
	_pollfd.push_back(pollfd());
	_pollfd.back().fd = new_fd;
	_pollfd.back().events = POLLIN;
	_nb_fd++;
}

int	Server::_trait_requests(pollfd pfd)
{
	int ret;
	int lines;
	int status;

	if ((ret = _recvAll(pfd)))
		return ret;
	_recvs.clear();
	lines = _fillRecvs(std::string(_buff));
	_buff.clear();
	for (int i = 0; i < lines; i++) {
		std::cout << DIS_RECV << pfd.fd << DIS_RECVEND(_recvs[i].first, _recvs[i].second) << std::endl;
		if ((status = _manageCmd(pfd, _recvs[i]))) {
			if (status == 2)
				break;
			else if (status == 3)
				_sendError(_user_dict[pfd.fd], ERR_UNKNOWNCOMMAND(_user_dict[pfd.fd]->getClient(), _user_dict[pfd.fd]->getNick(), _recvs[i].first));
			else if (status == 4) {
				run = 0;
				break;
			}
		}
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
			std::cout << "disconnect user... inprogress" << std::endl;
			// return _disconnectUser(_users[pollfd.fd], 0);
			// return 1;
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
	// _cmds.clear();
	// for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
	// 	delete (*it).second;
	// _channels.clear();
	for (std::map<int, User*>::iterator it = _user_dict.begin(); it != _user_dict.end(); it++)
		delete (*it).second;
	_users.clear();
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

Exception::err::err(const char *msg) : _msg(msg)
{
}
