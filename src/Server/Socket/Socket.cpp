/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:48:07 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/06 14:30:41 by rbutzke          ###   ########.fr       */
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
#include <cstdlib>

Socket::~Socket(){}

Socket::Socket(){
	std::memset(&_addr, 0, sizeof(_addr));
}

int		Socket::initTCP(const char *port, int events, const char *ip) {
	int socketFd = 0;
	try{
		initSocket(socketFd);
		setSocketReusable(socketFd);
		setPortReusable(socketFd);
		setAddr(port, ip);
		setAddrToSocket(socketFd);
		putSocketListeningLimit(socketFd, events);
		return (socketFd);
	} catch(std::exception &e) {
		std::cerr << e.what();
	}
	return (-1);
}

void	Socket::initSocket(int &socketFd){
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

void	Socket::setAddr(const char *port, const char *ip) {
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(strtol(port, 0, 10));
	inet_pton(AF_INET, ip, &_addr.sin_addr);
}

void	Socket::setAddrToSocket(int &socketFd){
	if (bind(socketFd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		throw std::runtime_error("error: failed to bind socket");
}

void	Socket::putSocketListeningLimit(int &socketFd, int &events){
	listen(socketFd, events);
}
