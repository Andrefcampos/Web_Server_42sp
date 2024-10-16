/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:24:17 by myokogaw          #+#    #+#             */
/*   Updated: 2024/10/16 18:09:16 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <exception>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <iostream>

Server::Server() : _port(8080), _ip(INADDR_ANY) {
	_socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);;
}

Server::Server(void){
	std::cout << "madeira\n";
};

Server::~Server(void){};

Server::Server(int const &port):_port(port) {
	std::memset(&_peer_addr, 0, sizeof(_peer_addr));
	_peer_addr.sin_addr.s_addr = htonl(_ip);
	_peer_addr.sin_port = htons(_port);
	_peer_addr.sin_family = AF_INET;
	_socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void	Server::bindSocket(void) {
	if (bind(_socketFd, (struct sockaddr *)&_peer_addr, sizeof(_peer_addr)) ==  -1) {
		throw std::runtime_error("Error: bind");
	}
}

void	Server::setOptSocket(void) {
	int i = 1;

	if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int)) == -1) {
		throw std::runtime_error("Error: setsockopt 1");
	}
	if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEPORT, &i, sizeof(int)) == -1) {
		throw std::runtime_error("Error: setsockopt 2");
	}
}

void	Server::listenSocket(void) {
	if (listen(_socketFd, 256) == -1) {
		throw std::runtime_error("Error: listen");
	}
}

int		Server::getSocketFd(void) const {
	return (_socketFd);
}

int	Server::initServer(void) {
	try {
		setOptSocket();
		bindSocket();
		listenSocket();
		return getSocketFd();
	}catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
