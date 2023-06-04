/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:53:46 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/04 23:47:34 by rle-thie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Irc.hpp"

User::User(int socket_desc)
{
	_sd = socket_desc;
	_user_name = "";
	_first_try = 1;
	_nick = "";
	_host_name = "";
	_tried_to_auth = 0;
	_auth = 0;
	_pwd = "";
}

std::string const User::getClient() const
{
	if (getFirstTry())
		return "";
	return (getNick() + "!" + getUserName() + "@" + getHostName());
}

// ---------- getter -----------

int const &User::getUserSd() const
{
	return _sd;
}

bool const &User::getAuth() const
{
	return _auth;
}

bool const &User::getTriedToAuth() const
{
	return _tried_to_auth;
}

bool const &User::getFirstTry() const
{
	return _first_try;
}

std::string const User::getNick() const
{
	if (_nick.empty())
		return "";
	return _nick;
}

std::string const &User::getUserName() const
{
	return _user_name;
}

std::string const &User::getHostName() const
{
	return _host_name;
}

std::string const &User::getPassword() const
{
	return _pwd;
}

// setter

void	User::setPass(std::string str)
{
	_pwd = str;
}

void	User::setNick(std::string str)
{
	_nick = str;
}

void	User::setUser(std::string str)
{
	_user_name = str;
}

void	User::setAuth(bool str)
{
	_auth = str;
}

User::~User()
{
}