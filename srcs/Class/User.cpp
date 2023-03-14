/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:53:46 by rle-thie          #+#    #+#             */
/*   Updated: 2023/03/13 14:56:59 by rle-thie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Irc.hpp"

User::User(int socket_desc)
{
	_sd = socket_desc;
	_pseudo = "NONE";
	_addr = "NONE";
}

User::~User()
{
}