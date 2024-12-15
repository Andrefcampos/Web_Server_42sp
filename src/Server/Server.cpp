/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:38:03 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/15 14:42:31 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Conf.hpp"
#include "Logger.hpp"
#include "Server.hpp"
#include "Request.hpp"
#include "Directive.hpp"
#include "Location.hpp"
#include <iostream>

using namespace std;

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

const Directive	*Server::getDirective(const string &directive) {
	
	return (this->_directives[directive]);
}

void	Server::setDirective(Directive *directive) {
	this->_directives[directive->getName()] = directive;
}

void	Server::sendResponse(int fd, Request *request) {
	Location *location = static_cast<LocationDirective *>(_directives["location"])->getLocation(request->getPath());

	if (request->getPath().compare("/") == 0)
		sendIndex(fd, (static_cast<const IndexDirective *>(location->getDirective("index")))->getIndex());
	else if (request->getPath().find(".ico") != string::npos || request->getPath().find(".png") != string::npos)
		sendImage(fd, "image/img.png");
	else
		sendIndex(fd, static_cast<RootDirective *>(location->getDirective("root"))->getRoot() + request->getPath());
}

void	Server::print(void) const {
	for (map<string, Directive *>::const_iterator it = _directives.begin(); it != _directives.end(); ++it) {
		it->second->print();
	}
}