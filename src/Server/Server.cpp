/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:38:03 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/16 20:55:52 by myokogaw         ###   ########.fr       */
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

Server::Server() : Socket() {
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
	Response response(request, getLocation(), getErrorPage());

	cout << endl << response.getResponseMsg() << endl;
	send(fd, response.getResponseMsg().c_str(),  response.getMsgSize(), 0);
}

void	Server::print(void) const {
	for (map<string, Directive *>::const_iterator it = _directives.begin(); it != _directives.end(); ++it) {
		it->second->print();
	}
}