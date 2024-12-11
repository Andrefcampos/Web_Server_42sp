/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:06:41 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/11 12:26:53 by myokogaw         ###   ########.fr       */
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

Request *ParseRequest::setBufferSocketFd(int fd){
	if (fd == -1)
		return 0;
	isNewClient(fd);
	setBuffer(fd);
	if (parseRequest(fd)){
		Request *request = _socket[fd].request;
		_socket.erase(fd);
		return request;
	}
	return NULL;
}

void	ParseRequest::isNewClient(int fd){
	if (not _socket.count(fd)){
		_socket[fd].lentgh = 0;
		_socket[fd].request = new Request();
		_socket[fd].startTime = time(0);
	}
}

int		ParseRequest::parseRequest(int fd){
	int	error = 0;

	try{
		if ((error = timeOutRequest(_socket[fd].startTime))){
			_socket[fd].request->setParserError(error);
			return 1;
		}
		if ((error = _socket[fd].request->setRequestLine(_socket[fd].buffer))){
			_socket[fd].request->setParserError(error);
			return 1;
		}
		_socket[fd].request->setHeader(_socket[fd].buffer);
		_socket[fd].request->setBody(_socket[fd].buffer);
	}catch( Request::RequestException &e){
		cout << e.what();
		return 0;
	}
	return 1;
}

void	ParseRequest::setBuffer(int fd){
	char	buffer[20 +1];
	int		bytesRead;

	memset(buffer, 0, 20+1);
	bytesRead = recv(fd, buffer, 20, MSG_DONTWAIT);
	_socket[fd].buffer.append(buffer, bytesRead);
}

int		ParseRequest::timeOutRequest(std::time_t timeStart){
	time_t maxTime = 10;

	if ((time(0) - timeStart) > maxTime)
		return 408;
	return 0;
}

void	ParseRequest::removeFD(int fd){
	_socket.erase(fd);
}