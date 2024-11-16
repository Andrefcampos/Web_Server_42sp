/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:38:03 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 17:58:37 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>

Server::~Server(){};

Server::Server(int port, int events, std::string hostName, std::string ip)
:Socket(), _port(port), _maxEvents(events), _ip(ip){
	_hostName = hostName;
	initTCP(_socketFd, _port, _maxEvents, _ip.c_str());
};

int		Server::getSocketFd() const{
	return _socketFd;
}

std::string Server::getHostName() const{
	return _hostName;
}

int			Server::getMaxEvent() const{
	return _maxEvents;
}

void	Server::sendResponse(int fd){
	sendIndex(fd, this->getPathIndex());
	sendImage(fd, this->getPathImage());
}
