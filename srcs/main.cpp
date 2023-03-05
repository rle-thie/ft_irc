/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:24:07 by rle-thie          #+#    #+#             */
/*   Updated: 2023/03/05 16:00:46 by rle-thie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Irc.hpp"

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
	Server irc(av[1], av[2]);
	try
	{
		irc.init();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		
	}
	

	return 0;
}
