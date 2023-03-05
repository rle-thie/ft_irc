/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-thie <rle-thie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:54:43 by rle-thie          #+#    #+#             */
/*   Updated: 2023/03/05 17:26:17 by rle-thie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEPTION_HPP
#define EXEPTION_HPP

#include <exception>

class Exception
{
	public :
		class getaddrinfo : public std::exception
		{
			const char	*what() const throw()
			{
				return "can't copy information from adress";
			}
		};

		class nobind : public std::exception
		{
			const char	*what() const throw()
			{
				return "no bind";
			}
		};

		class listen : public std::exception
		{
			const char	*what() const throw()
			{
				return "cant listen";
			}
		};

};

#endif