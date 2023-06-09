#ifndef IRC_HPP
#define IRC_HPP

#define BUFFER_SIZE 4096

#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <vector>
#include <signal.h>
#include <cerrno>
#include <arpa/inet.h>
#include <map>
#include <ctime>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "Channel.hpp"
#include "User.hpp"
#include "Server.hpp"
#include "Exception.hpp"
#include "Display.hpp"

std::string	currentTime();

#endif