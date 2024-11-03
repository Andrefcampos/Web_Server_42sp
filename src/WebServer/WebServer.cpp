/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:21:13 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/01 16:29:30 by rbutzke          ###   ########.fr       */
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
		initEvents();
		initServicesAddSocket();		
	}catch(std::exception &e){
		std::cerr << e.what();
	}
}

void	WebService::createEpoll(){
	if ((_epollfd = epoll_create1(EPOLL_CLOEXEC)) == -1)
		throw std::runtime_error("error: epoll_create1()");
}

void	WebService::initEvents(){
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

int	WebService::responseClient(int fd, std::string resp){
	_it = _services.begin();
	_ite = _services.end();
	while(_it != _ite){
		
		if (resp.find("Host: localhost:8080") != std::string::npos)
		{
			if (resp.find("Accept: text/html") != std::string::npos)
			{
				_it->second.sendResponseHTML(fd, "index/index.html");
				std::cout << "index\n";
			}
			else if (resp.find("Accept: image/avif") != std::string::npos){
				_it->second.sendResponseImage(fd, "image/images.png");
				std::cout << "image\n";
			}
			if (epoll_ctl(_epollfd, EPOLL_CTL_DEL, _ev.data.fd, &_ev) == -1)
				throw std::runtime_error("error: epoll_ctl()");
			close(fd);
			break ;
		}
		else{
			if (resp.find("Accept: text/html") != std::string::npos)
				_it->second.sendResponseHTML(fd, "index/index2.html");
			else if (resp.find("Accept: image/avif") != std::string::npos)
				_it->second.sendResponseImage(fd, "image/img.png");
			if (epoll_ctl(_epollfd, EPOLL_CTL_DEL, _ev.data.fd, &_ev) == -1)
				throw std::runtime_error("error: epoll_ctl()");
			close(fd);
			break ;
		}
		_it++;
	}
	resp = "";
	return (0);
}

WebService::~WebService(){}

WebService::WebService(){}