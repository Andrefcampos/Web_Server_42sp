/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:06:41 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/14 17:21:18 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ParseRequest.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <sys/socket.h>
#include "utils.hpp"
#include "Client.hpp"

Request *ParseRequest::setBufferSocketFd(Client *client){
	if (client->getFdClient() == -1)
		return 0;
	isNewClient(client->getFdClient());
	setBuffer(client->getFdClient());
	if (parseRequest(client->getFdClient(), client)){
		Request *request = _socket[client->getFdClient()].request;
		_socket.erase(client->getFdClient());
		return request;
	}
	return NULL;
}

void	ParseRequest::isNewClient(int fd){
	if (not _socket.count(fd)){
		_socket[fd].lentgh = 0;
		_socket[fd].request = new Request();
	}
}

int		ParseRequest::parseRequest(int fd, Client *client){
	int	error = 0;

	try{
		cout << _socket[fd].buffer << "\n";
		if ((error = _socket[fd].request->setRequestLine(_socket[fd].buffer))){
			_socket[fd].request->setParserError(error);
			return 1;
		}
		if ((error = _socket[fd].request->setHeader(_socket[fd].buffer, client))){
			_socket[fd].request->setParserError(error);
			return 1;
		}
		if ((error = _socket[fd].request->setBody(_socket[fd].buffer))){
			_socket[fd].request->setParserError(error);
			return 1;
		}
	}catch( Request::RequestException &e){
		cout << e.what();
		return 0;
	}
	return 1;
}

void	ParseRequest::setBuffer(int fd){
	char	buffer[4012 +1];
	int		bytesRead;

	memset(buffer, 0, 4012 +1);
	bytesRead = recv(fd, buffer, 4012, MSG_DONTWAIT);
	_socket[fd].buffer.append(buffer, bytesRead);
}

void	ParseRequest::removeFD(int fd){
	_socket.erase(fd);
}