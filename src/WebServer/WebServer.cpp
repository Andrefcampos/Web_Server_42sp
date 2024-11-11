/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:21:13 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/11 14:27:21 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"
#include <iterator>
#include <stdexcept>
#include <map>
#include <iostream>
#include <unistd.h>

WebService::WebService(std::map<std::string, Server> services):
_services(services){
	initEpollStruct();
	try{
		createEpoll();
		initServicesAddSocket();
	}catch(std::exception &e){
		std::cerr << e.what();
	}
}

void	WebService::createEpoll(){
	if ((_epollfd = epoll_create1(EPOLL_CLOEXEC)) == -1)
		throw std::runtime_error("error: epoll_create1()");
	_ev.events = EPOLLIN;
}

void	WebService::initServicesAddSocket(){
	_it = _services.begin();
	_ite = _services.end();
	for(;_it != _ite; _it++){
		_ev.data.fd = _it->second.getSocketFd();
		_maxEvents += _it->second.getMaxEvent();
		if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, _ev.data.fd, &_ev) == -1)
			throw std::runtime_error("error: epoll_ctl()");
	}
}

void	WebService::loopingEvent(){
	while(1){
		_nfds = epoll_wait(_epollfd, _events, _maxEvents, -1);
		for(int index_epoll = 0; index_epoll < _nfds; index_epoll++){
			if (isNewClient(index_epoll))
				continue ;
			if (readFdClient(_events[index_epoll])){
				std::cout << "Entrou \n";
				static_cast<Server*>(_events[index_epoll].data.ptr)->sendResponse(_events[index_epoll].data.fd, _httpRequest);
				//responseClient(_events[index_epoll].data.fd);
				if (epoll_ctl(_epollfd, EPOLL_CTL_DEL, _events[index_epoll].data.fd, &_ev) == -1)
					throw std::runtime_error("error: epoll_ctl()");
				close(_events[index_epoll].data.fd);
			}
		}
	}
}

int	WebService::isNewClient(int index){
	_it = _services.begin();
	for(;_it != _services.end(); _it++){
		if (_events[index].data.fd == _it->second.getSocketFd()){
			_ev.data.fd = accept(_it->second.getSocketFd(), 0, 0);
			_events[index].data.ptr = &_it->second;
			if (_ev.data.fd == -1)
				throw std::runtime_error("error: accept()");
			_ev.events = EPOLLIN;
			if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, _ev.data.fd, &_ev) == -1)
				throw std::runtime_error("error: epoll_ctl()");
			return (1);
		}
	}
	return (0);
}

int	WebService::responseClient(int fd){
	std::string	server = _httpRequest["Headers"]["Host"];
	_services[server].sendResponse(fd, _httpRequest);
	return (0);
}

WebService::~WebService(){}

WebService::WebService(){}


void	WebService::initEpollStruct(){
	for(int i = 0; i < 80; i++)
		std::memset(&_events[i], 0, sizeof(_events[i]));
	std::memset(&_ev, 0, sizeof(_ev));
	_maxEvents = 0;
	_epollfd = 0;
}