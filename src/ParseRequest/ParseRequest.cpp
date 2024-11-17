/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:06:41 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/16 18:52:06 by rbutzke          ###   ########.fr       */
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

int	ParseRequest::setBufferSocketFd(int fd){
	if (fd == -1)
		return 0;
	isNewSocket(fd);
	setBuffer(fd);
	if (setBody(fd))
		cout << "HAVE BODY \n\n";
	if (parseRequest(fd))
		return (1);
	return 0;
}

int		ParseRequest::findBody(int fd){
	if (_socket[fd].buffer.find(""))
		return 1;
	return 0;
}

void	ParseRequest::isNewSocket(int fd){
	if (not _socket.count(fd)){
		_socket[fd].lentgh = 0;
		_socket[fd].request = new Request();
	}
}

int		ParseRequest::setBody(int fd){
	if (_socket[fd].parsedBody == false)
		return false;
	return true;
}

int		ParseRequest::parseRequest(int fd){
	try{
		_socket[fd].request->setRequestLine(_socket[fd].buffer);
		_socket[fd].request->setHeader(_socket[fd].buffer);
		_socket[fd].request->setBody(_socket[fd].buffer);
	}catch(exception &e){
		cout << e.what();
		return 0;
	}
	return 1;
}

void	ParseRequest::setBuffer(int fd){
	char	buffer[BUFFER_SIZE +1];
	int		bytesRead;

	memset(buffer, 0, BUFFER_SIZE+1);
	bytesRead = recv(fd, buffer, BUFFER_SIZE, MSG_DONTWAIT);
	_socket[fd].buffer.append(buffer, bytesRead);
}