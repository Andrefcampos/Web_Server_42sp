/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:21:13 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/11 22:07:28 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iterator>
#include <stdexcept>
#include <map>
#include <iostream>
#include <unistd.h>
#include "Webserv.hpp"
#include "Directive.hpp"

Webserv manager;

Webserv::Webserv() {		
	_conf["server"] = new ServerDirective();
};

Webserv::~Webserv() {
	for (std::map<std::string, Directive *>::iterator it = _conf.begin(); it != _conf.end(); ++it)
		delete it->second;
	_conf.clear();
};

// Webserv::Webserv(std::map<std::string, Server> services):
// _services(services){
// 	_maxEvents = 0;
// 	try{
// 		createEpoll();
// 		initServicesAddSocket();		
// 	}catch(std::exception &e){
// 		std::cerr << e.what();
// 	}
// }

// void	Webserv::createEpoll(){
// 	if ((_epollfd = epoll_create1(EPOLL_CLOEXEC)) == -1)
// 		throw std::runtime_error("error: epoll_create1()");
// 	_ev.events = EPOLLIN;
// }

// void	Webserv::initServicesAddSocket(){
// 	_it = _services.begin();
// 	_ite = _services.end();
// 	while(_it != _ite){
// 		int fd = _it->second.getSocketFd();
// 		_maxEvents += _it->second.getMaxEvent();
// 		_ev.data.fd = fd;
// 		if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &_ev) == -1)
// 			throw std::runtime_error("error: epoll_ctl()");
// 		_it++;
// 	}
// }

void	Webserv::loopingEvent(){
	while (true) {
		_nfds = epoll_wait(_epollfd, _events, _maxEvents, -1);
		for(int index_epoll = 0; index_epoll < _nfds; index_epoll++){
			if (not isNewClient(index_epoll))
				readFdClient(_events[index_epoll], _ev, _epollfd);
		}
	}
}

// int	Webserv::isNewClient(int index){
// 	_it = _services.begin();
// 	_ite = _services.end();
// 	while(_it != _ite){
// 		if (_events[index].data.fd == _it->second.getSocketFd()){
// 			_ev.data.fd = accept(_it->second.getSocketFd(), 0, 0);
// 			if (_ev.data.fd == -1)
// 				throw std::runtime_error("error: accept()");
// 			_ev.events = EPOLLIN;
// 			if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, _ev.data.fd, &_ev) == -1)
// 				throw std::runtime_error("error: epoll_ctl()");
// 			return (1);
// 		}
// 		_it++;
// 	}
// 	return (0);
// }

// int	Webserv::responseClient(int fd, std::string resp){
// 	_it = _services.begin();
// 	_ite = _services.end();
// 	while(_it != _ite){
// 		if (resp.find("Host: localhost:8080") != std::string::npos)
// 		{
// 			if (resp.find("Accept: text/html") != std::string::npos)
// 				_it->second.sendResponseHTML(fd, "index/index.html");
// 			else if (resp.find("Accept: image/avif") != std::string::npos)
// 				_it->second.sendResponseImage(fd, "image/images.png");
// 			break ;
// 		}
// 		else{
// 			if (resp.find("Accept: text/html") != std::string::npos)
// 				_it->second.sendResponseHTML(fd, "index/index2.html");
// 			else if (resp.find("Accept: image/avif") != std::string::npos)
// 				_it->second.sendResponseImage(fd, "image/img.png");
// 			break ;
// 		}
// 		_it++;
// 	}
// 	resp = "";
// 	return (0);
// }

// Webserv::~Webserv(){}

// Webserv::Webserv(){}