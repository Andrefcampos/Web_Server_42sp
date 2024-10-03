/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateEpoll.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:57:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/10/03 15:00:05 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CreateEpoll.hpp"
#include <stdexcept>
#include <exception>
#include <fcntl.h>
#include <iostream>

CreateEpoll::CreateEpoll(Socket *socketFds, int nbrCliente){
	this->_socketFds = socketFds;
	this->_nbrCliente = nbrCliente;
	this->_events = new struct epoll_event[MAX_EVENTS];
	this->_epollfd = initEpoll();

	for(int i = 0; i < _nbrCliente; i++){
		try{
			addEpoll(socketFds[i].getSocket());
		}catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		}
	}
}

CreateEpoll::~CreateEpoll(){
	delete _socketFds;
	delete _events;
}

int	CreateEpoll::initEpoll(){
	int epollFd;

	if ((epollFd = epoll_create1(EPOLL_CLOEXEC)) == -1){
		throw std::runtime_error("epoll_create1");
	}
	return (epollFd);
}

void	CreateEpoll::addEpoll(int fd){
	struct epoll_event	ev;

	ev.events = EPOLLIN;
	ev.data.fd = setnonblocking(fd);
	if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1){
		throw std::runtime_error("epoll_ctl");
	}
}

int CreateEpoll::getEpoll(){
	return (this->_epollfd);
}

struct epoll_event* CreateEpoll::getEpollEvent(){
	return (this->_events);
}

int CreateEpoll::setnonblocking(int sock)
{
    int result;
    int flags;

    flags = fcntl(sock, F_GETFL, 0);
    if (flags == -1)
        return -1;
    flags |= O_NONBLOCK;
    result = fcntl(sock, F_SETFL ,flags);
    return result;
}