/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:37:59 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/12 03:42:43 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Socket.hpp"
# include "Response.hpp"
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
		
		// std::map<std::string, Location *> _locations;

	public:
		Server();
		~Server();
		// Server():_hostName(""){};
		// Server(int port, int events, std::string hostName, std::string ip);
		// int			getSocketFd() const;
		// int			getMaxEvent() const;
		// std::string	getHostName() const;
};