/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:24:07 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/05 19:17:19 by rle-thie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Irc.hpp"

bool run = true;

std::string Server::_current_time()
{
	time_t t = std::time(0);
	struct tm *now = std::localtime(&t);
	std::string time(asctime(now));
	time.erase(time.end() - 1);
	return time;
}

void	signal_checker(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
		run = false;
}

int	ft_error(std::string str)
{
	std::cerr << str << std::endl;
	return (1);
}

int	parser(int ac, char **av)
{
	std::string port = av[1];
	std::string pswd = av[2];
	if (ac != 3)
		return (ft_error("wrong number of arguments"));
	if (port.length() == 4 || port.length() == 5)
	{
		if (atoi(av[1]) < 1024 || atoi(av[1]) > 65535)
			return(ft_error("port must be 1024-65535"));
	}
	else
		return(ft_error("port must be 1024-65535"));
	
	if (pswd.length() < 1)
		return(ft_error("wrong password"));
	return (0);
}

int main(int ac, char **av)
{

	if (parser(ac, av))
		return (1);
	Server *irc = new Server(av[1], av[2]);
	try
	{
		irc->init();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error\nServer cannot init" << '\n';
		std::cerr << e.what() << '\n';
		delete irc;
	}
	while (run == true)
	{
		try
		{
			signal(SIGINT, signal_checker);
			signal(SIGQUIT, signal_checker);
			irc->start();
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			delete irc;
			return (1);
		}
	}
	delete irc;
	return 0;
}
