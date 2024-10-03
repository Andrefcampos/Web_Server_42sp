/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:03:49 by andrefil          #+#    #+#             */
/*   Updated: 2024/10/03 11:44:05 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include <cstring>
#include <exception>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <iostream>

Socket::Socket(void){};
Socket::~Socket(void){};

Socket::Socket(int const &port):_port(port) {
	std::memset(&_peer_addr, 0, sizeof(_peer_addr));
	_peer_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	_peer_addr.sin_port = htons(_port);
	_peer_addr.sin_family = AF_INET;
	_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void	Socket::bindSocket(void) {
	if (bind(_fd, (struct sockaddr *)&_peer_addr, sizeof(_peer_addr)) ==  -1) {
		throw std::runtime_error("Error: bind");
	}
}

void	Socket::setOptSocket(void) {
	int i = 1;

	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int)) == -1) {
		throw std::runtime_error("Error: setsockopt 1");
	}
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEPORT, &i, sizeof(int)) == -1) {
		throw std::runtime_error("Error: setsockopt 2");
	}
}

void	Socket::listenSocket(void) {
	if (listen(_fd, 256) == -1) {
		throw std::runtime_error("Error: listen");
	}
}

int	Socket::createSocket(void) {
	try {
		setOptSocket();
		bindSocket();
		listenSocket();
		return getSocket();
	}catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

int		Socket::getSocket(void) const {
	return (_fd);
}
