/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:06:41 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 21:17:40 by rbutzke          ###   ########.fr       */
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
	memset(buffer, 0, BUFFER_SIZE+1);
	bytesRead =  recv(fd, buffer, BUFFER_SIZE, MSG_DONTWAIT);
	_socket[fd].buffer.append(buffer, bytesRead);
	if (setBody(fd))
		cout << "HAVE BODY \n\n";
	if (_socket[fd].buffer.find("\r\n\r\n") != string::npos)
		return (parseRequestLineHeaders(fd));
	return 0;
}

void	ParseRequest::isNewSocket(int fd){
	if (not _socket.count(fd)){
		_socket[fd].haveBody = false;
		_socket[fd].lentgh = 0;
	}
}

int		ParseRequest::setBody(int fd){
	if (_socket[fd].haveBody == false)
		return false;
	return true;
}

int		ParseRequest::parseRequestLineHeaders(int fd){
	string temp;

	temp = getLine<string, string>(_socket[fd].buffer, "\r\n");
	if (temp.empty())
		return 1;
	_socket[fd].request.setRequestLine(temp);

	cout << _socket[fd].request.getMethod() << '\n';
	cout << _socket[fd].request.getPath() << '\n';
	cout << _socket[fd].request.getVersion() << "\n\n";
	
	temp = getLine<string, string>(_socket[fd].buffer, "\r\n\r\n");
	_socket[fd].request.parseHeaders(temp);
	putMapList(_socket[fd].request.getAllHeader());
	exit(1);
	return 0;
}

