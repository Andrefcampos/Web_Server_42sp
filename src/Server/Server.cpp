/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:38:03 by rbutzke           #+#    #+#             */
/*   Updated: 2024/10/23 18:09:38 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::~Server(){};

Server::Server(int port, int events, std::string hostName, std::string ip)
:Socket(), _port(port), _maxEvents(events), _ip(ip){
	if (hostName.empty())
		_hostName = "";
	initTCP(_socketFd, _port, _maxEvents, _ip.c_str());
};

int		Server::getSocketFd() const{
	return _socketFd;
}

std::string Server::getHostName() const{
	return _hostName;
}

int			Server::getMaxEvent() const{
	return _maxEvent;
}