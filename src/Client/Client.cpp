/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:33:23 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/11 12:33:23 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <unistd.h>

Client::Client(Server *server, int fdClient) : _server(server), _socketFdClient(fdClient) {
	_request = NULL;
	_startTime = std::time(0);
};

Client::~Client() {
	/* close(this->_socketFdClient); */
}

Server *Client::getServer(void) const {
	return (this->_server);
}

int		Client::getFdClient(void) const {
	return (this->_socketFdClient);
}

void	Client::setRequest(Request *request) {
	this->_request = request;
}

Request	*Client::getRequest(void) const {
	return (this->_request);
}

void			Client::setMaxSize(long long int maxSize){
	this->_maxSize = maxSize;
}

long long int	Client::getMaxSize() const{
	return _maxSize;
}

int		Client::timeOut(void) {
	return ((time(0) - _startTime) > 10) ? 408 : 0;
}
