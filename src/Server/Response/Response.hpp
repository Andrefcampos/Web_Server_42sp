/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:07:34 by rbutzke           #+#    #+#             */
/*   Updated: 2024/10/31 16:04:52 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <sys/socket.h>

class Response
{
	private:
		std::string	_fillHttp[4][4];
		std::string	_htpp;
		std::string	_status[4];
		std::string	_type[3];
		std::string	_connection[3];
		std::string	_length[3];
		std::string	_body;
		void 		clean();

	public:
		Response();
		~Response();
		void setStatus(std::string value, std::string reason);
		void setType(std::string type);
		void setConnection(std::string connection);
		void setLength(std::string length);
		void setBody(std::string body);
		std::string	getHttp();

		void	sendResponseHTML(int fd, std::string indexHTML);
		void	sendResponseImage(int fd, std::string image);		
};

enum e_response
{
	STATUS = 0,
	TYPE,
	CONNECTION,
	LENGTH,
};

enum e_status
{
	HTTP_VERSION = 0,
	VALUE,
	REASON,
	END_LINE,
};

enum e_header
{
	HEADER = 0,
	HEADER_TYPE,
	ENDL,
};