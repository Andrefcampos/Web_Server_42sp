/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:21:13 by rbutzke           #+#    #+#             */
/*   Updated: 2024/10/23 18:15:45 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"
#include <iterator>
#include <stdexcept>
#include <map>

WebService::~WebService(){}
WebService::WebService(){}

WebService::WebService(std::map<std::string, Server> services):
_services(services){
	_maxEvents = 0;
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
			throw std::runtime_error("error: epoll_create1()");
		_it++;
	}
}

void	WebService::loopingEvent(){
	while(1){
		_nfds = epoll_wait(_epollfd, _events, _maxEvents, -1);
		for (int i = 0; i < _nfds; i++){
			_ite = _services.end();
			for(_it = _services.begin(); _it != _ite; _it++){
				
			}
		}



		
	}
}