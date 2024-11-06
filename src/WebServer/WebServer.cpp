/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:21:13 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/06 16:38:15 by rbutzke          ###   ########.fr       */
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
	_maxEvents = 0;
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
	while(_it != _ite){
		int fd = _it->second.getSocketFd();
		_maxEvents += _it->second.getMaxEvent();
		_ev.data.fd = fd;
		if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &_ev) == -1)
			throw std::runtime_error("error: epoll_ctl()");
		_it++;
	}
}

void	WebService::loopingEvent(){
	while(1){
		_nfds = epoll_wait(_epollfd, _events, _maxEvents, -1);
		for(int index_epoll = 0; index_epoll < _nfds; index_epoll++){
			if (not isNewClient(index_epoll))
				readFdClient(_events[index_epoll], _ev, _epollfd);
		}
	}
}

int	WebService::isNewClient(int index){
	_it = _services.begin();
	_ite = _services.end();
	while(_it != _ite){
		if (_events[index].data.fd == _it->second.getSocketFd()){
			_ev.data.fd = accept(_it->second.getSocketFd(), 0, 0);
			if (_ev.data.fd == -1)
				throw std::runtime_error("error: accept()");
			_ev.events = EPOLLIN;
			if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, _ev.data.fd, &_ev) == -1)
				throw std::runtime_error("error: epoll_ctl()");
			return (1);
		}
		_it++;
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



/* 	_it = _services.begin();
_ite = _services.end();
while(_it != _ite){
if (resp.find("Host: localhost:8080") != std::string::npos)
{
	if (resp.find("Accept: text/html") != std::string::npos)
		_it->second.sendResponse(fd, "index/index.html");
	else if (resp.find("Accept: image/avif") != std::string::npos)
		_it->second.sendImage(fd, "image/images.png");
	break ;
}
else{
	if (resp.find("Accept: text/html") != std::string::npos)
		_it->second.sendResponse(fd, "index/index2.html");
	else if (resp.find("Accept: image/avif") != std::string::npos)
		_it->second.sendImage(fd, "image/img.png");
	break ;
}
_it++;
}
resp = ""; */