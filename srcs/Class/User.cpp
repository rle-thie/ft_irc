/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevy <ldevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:53:46 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/06 17:49:07 by ldevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Irc.hpp"

User::User(int socket_desc, std::string hostname)
{
	_sd = socket_desc;
	_user_name = "";
	_first_try = 1;
	_nick = "";
	_host_name = hostname;
	_auth = 0;
	_pwd = "";
	_cap = 0;
	_isope = false;
}

std::string const User::getClient() const
{
	return (getNick() + "@" + getHostName());
}

// ---------- getter -----------

bool const &User::getOpe() const
{
	return _isope;
}

int const &User::getUserSd() const
{
	return _sd;
}

bool const &User::getAuth() const
{
	return _auth;
}

bool const &User::getCap() const
{
	return _cap;
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

void	User::setCap(bool str)
{
	_cap = str;
}

void	User::setOpe(bool a)
{
	_isope = a;
}

User::~User()
{
}