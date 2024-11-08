/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:48:07 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/07 10:21:49 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include <iostream>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>
#include <unistd.h>

Socket::~Socket(){}

Socket::Socket(){
	std::memset(&_addr, 0, sizeof(_addr));
}

void	Socket::initTCP(int &socketFd, int &port, int &events, const char *ip){
	try{
		initSocket(socketFd);
		setSocketReusable(socketFd);
		setPortReusable(socketFd);
		setAddr(socketFd, port, ip);
		setAddrToSocket(socketFd);
		putSocketListeningLimit(socketFd, events);
	}catch(std::exception &e){
		std::cerr << e.what();
	}
}

void	Socket::initSocket(int & socketFd){
	socketFd = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);
	if (socketFd == -1)
		throw std::runtime_error("error: socket()");
}

void	Socket::setSocketReusable(int &socketFd){
	int enable = 1;

	if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
		throw std::runtime_error("error: setsockopt()");
}

void	Socket::setPortReusable(int &socketFd){
	int enable = 1;

	if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) == -1)
		throw std::runtime_error("error: setsockopt()");
}

void	Socket::setAddr(int socketFd, int &port, const char *ip){
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, ip, &_addr.sin_addr) <= 0){
		   close(socketFd);
        throw std::runtime_error("error: invalid IP address");
	}
}

void	Socket::setAddrToSocket(int &socketFd){
	if (bind(socketFd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		throw std::runtime_error("error: failed to bind socket");
}

void	Socket::putSocketListeningLimit(int &socketFd, int &events){
	listen(socketFd, events);
}
