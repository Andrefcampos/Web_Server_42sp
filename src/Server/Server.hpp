/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:37:59 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/16 11:18:11 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include <string>

class Server : public Socket, public Response {
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
		void		sendResponse(int fd, Request *request);
};
