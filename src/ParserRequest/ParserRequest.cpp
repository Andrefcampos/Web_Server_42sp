/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefil <andrefil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:16:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/08 03:06:46 by andrefil         ###   ########.fr       */
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


void	ParserRequest::readFdClient(epoll_event &events, epoll_event &ev, int &epollfd){
	char		buffer[BUFFERSIZE +1];
	ssize_t		bufferRead;
	std::memset(buffer, 0, BUFFERSIZE+1);

	bufferRead = recv(events.data.fd, buffer, BUFFERSIZE, MSG_DONTWAIT);
	_oneRequest[events.data.fd] += buffer;
	if (bufferRead == -1)
		std::runtime_error("error: recv()");
	if (_oneRequest[events.data.fd].find("\r\n\r\n") != std::string::npos){
		parseHttpClient(_oneRequest[events.data.fd]);
		responseClient(events.data.fd);
		_oneRequest.erase(events.data.fd);
		if (epoll_ctl(epollfd, EPOLL_CTL_DEL, ev.data.fd, &ev) == -1)
			throw std::runtime_error("error: epoll_ctl()");
		close(ev.data.fd);
		return ;
	}
}

void	ParserRequest::parseHttpClient(std::string htppRequest){
	std::list<std::string>	tokens;

	tokens = split(htppRequest, '\n');
	_httpRequest["requestLine"] = setRequestLine(*tokens.begin());
	tokens.remove(*tokens.begin());
	_httpRequest["Headers"] = setHeaders(tokens);
}

ParserRequest::ParserRequest(){}
ParserRequest::~ParserRequest(){}
