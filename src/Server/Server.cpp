/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:38:03 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/08 15:34:28 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Conf.hpp"
#include "Logger.hpp"
#include "Server.hpp"
#include "Request.hpp"
#include <iostream>

using namespace std;

// Server::~Server(){};

// Server::Server(int port, int events, string hostName, string ip)
// :Socket(), _port(port), _maxEvents(events), _ip(ip){
// 	if (hostName.empty())
// 		_hostName = "";
// 	else
// 		_hostName = hostName;
// 	initTCP(_socketFd, _port, _maxEvents, _ip.c_str());
// };

void	Server::setSocketFd(const int socketFd) {
	this->_socketFd = socketFd;
}

int		Server::getSocketFd() const {
	return (this->_socketFd);
}

Server::Server() : Socket(), Response() {
	this->_directives["listen"] = new ListenDirective();
	this->_directives["location"] = new LocationDirective();
	this->_directives["client_max_body_size"] = new ClientMaxBodySizeDirective();
	this->_directives["error_page"] = new ErrorPageDirective();
}

Server::~Server() {
	for (map<string, Directive *>::iterator it = _directives.begin(); it != _directives.end(); ++it)
		delete it->second;
	_directives.clear();
}

Directive	*Server::getDirective(const string &directive) {
	return (_directives[directive]);
}

void	Server::sendResponse(int fd, Request *request){
	if (request->getPath() == "/")
		sendIndex(fd, this->getPathIndex());
	else if (request->getPath() == "/css/styles.css")
		sendIndex(fd, this->getPathImage());
	else
		sendImage(fd, this->getPathImage());
}
