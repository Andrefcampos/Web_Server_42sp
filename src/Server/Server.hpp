/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:37:59 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/03 17:39:10 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Socket.hpp"
# include "Response.hpp"
# include "Directive.hpp"
# include <string>
# include <map>

class Location;

class Server : public Socket, public Response {
	private:
		// int			_socketFd;
		// int 		_port;
		// int 		_maxEvents;
		// std::string	_ip;
		// std::string _hostName;
		std::map<std::string, Directive *> _directives;

	public:
		Server();
		virtual ~Server();

		Directive *getDirective(const std::string &directive);
		// void	setDirective(Conf &cf);
		// Server():_hostName(""){};
		// Server(int port, int events, std::string hostName, std::string ip);
		// int			getSocketFd() const;
		// int			getMaxEvent() const;
		// std::string	getHostName() const;
		friend class ServerNameHandler;
		friend class ClientMaxBodySizeHandler;
		friend class LocationHandler;
		friend class ListenHandler;
		friend class ErrorPageHandler;
};