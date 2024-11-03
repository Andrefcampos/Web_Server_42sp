/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:16:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/01 16:30:58 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParserRequest.hpp"
#include <sys/socket.h>
#include <stdexcept>
#include <iostream>

void	ParserRequest::readFdClient(epoll_event &events, epoll_event &ev, int &epollfd){
	char		_buffer[BUFFERSIZE +1];
	ssize_t		bufferRead;
	std::memset(_buffer, 0, BUFFERSIZE+1);

	bufferRead = recv(events.data.fd, _buffer, BUFFERSIZE, MSG_DONTWAIT);
	if (bufferRead == -1)
		std::runtime_error("error: recv()");
	ev.events = EPOLLIN;
	if (epoll_ctl(epollfd, EPOLL_CTL_MOD, ev.data.fd, &ev) == -1)
		throw std::runtime_error("error: epoll_ctl()");
	if (std::string(_buffer).find("\r\n\r\n") != std::string::npos)
	{
		_oneRequest[events.data.fd] += _buffer;
		std::cout << _oneRequest[events.data.fd];
		responseClient(events.data.fd, _oneRequest[events.data.fd]);
		_oneRequest.erase(events.data.fd);
		return ;
	}
	else
		_oneRequest[events.data.fd] += _buffer;
	(void)ev;
}

ParserRequest::ParserRequest(){}

ParserRequest::~ParserRequest(){}
