/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevy <ldevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:54:43 by rle-thie          #+#    #+#             */
/*   Updated: 2023/06/16 13:04:24 by ldevy            ###   ########.fr       */
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

		class err : public std::exception
		{
			public :
				err(const char *msg);
			private :
				const char	*_msg;
			const char	*what() const throw()
			{
				return _msg;
			}
		};

};

#endif

