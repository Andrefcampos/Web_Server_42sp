/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefil <andrefil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:37:59 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/08 03:07:49 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket.hpp"
#include "Response.hpp"
#include <string>

class Server : public Socket, public Response{
	private:
		int			_socketFd;
		int 		_port;
		int 		_maxEvents;
		std::string	_ip;
		std::string _hostName;

	public:
		~Server();
		Server():_hostName(""){};
		Server(int port, int events, std::string hostName, std::string ip);
		int			getSocketFd() const;
		int			getMaxEvent() const;
		std::string	getHostName() const;
		void		sendResponse(int fd, httpRequest http);
};
