/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:16:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/07 20:09:24 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParserRequest.hpp"
#include <sys/socket.h>
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <list>
#include <string>
#include <iterator>
#include "split.hpp"
#include <cstdlib>

int	ParserRequest::readFdClient(epoll_event &events){
	char		buffer[BUFFERSIZE +1];
	ssize_t		bufferRead;
	std::memset(buffer, 0, BUFFERSIZE+1);

	if (not _oneRequest.count(events.data.fd)){
		_oneRequest[events.data.fd].haveBody = false;
		_oneRequest[events.data.fd].lentgh = 0;
	}
	if (_oneRequest[events.data.fd].haveBody){
		bufferRead = recv(events.data.fd, buffer, BUFFERSIZE, MSG_DONTWAIT);
		_oneRequest[events.data.fd].buffer += buffer;
		if (_oneRequest[events.data.fd].buffer.size() == _oneRequest[events.data.fd].lentgh){
			_httpRequest["Body"]["Body"] = _oneRequest[events.data.fd].buffer;
			return 1;
		}
		return 0;
	}
	if (_oneRequest[events.data.fd].haveBody == false){
		bufferRead = recv(events.data.fd, buffer, BUFFERSIZE, MSG_DONTWAIT);
		_oneRequest[events.data.fd].buffer += buffer;
		if (bufferRead == -1)
			std::runtime_error("error: recv()");
		if (_oneRequest[events.data.fd].buffer.find("\r\n\r\n") != std::string::npos){
			if (parseHttpClient(_oneRequest[events.data.fd])){
				_oneRequest.erase(events.data.fd);
				return 0;
			}
			_oneRequest.erase(events.data.fd);
			return (1);
		}
	}
	return 0;
}

int	ParserRequest::parseHttpClient(bufferFD buffer){
	std::list<std::string>	tokens;

	tokens = split(buffer.buffer, '\n');
	_httpRequest["requestLine"] = setRequestLine(*tokens.begin());
	tokens.remove(*tokens.begin());
	_httpRequest["Headers"] = setHeaders(tokens);
	putMap(_httpRequest["requestLine"]);
	putMap(_httpRequest["Headers"]);
	if (_httpRequest["Headers"].count("Content-Length")){
		buffer.haveBody = true;
		buffer.lentgh = std::atoll(_httpRequest["Headers"]["Content-Length"].c_str());
		std::cout << "entrou \n";
		return 1;
	}
	return 0;
}

ParserRequest::ParserRequest(){}
ParserRequest::~ParserRequest(){}