/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:19:25 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/11 22:07:28 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include <sys/epoll.h>
#include <string>
#include <iterator>
#include <map>
#include <iostream>
#include "ParseRequest.hpp"

// class Webserv : public ParseRequest {
// 	private:
// 		std::map<std::string, Server>			_services;
// 		std::map<std::string, Server>::iterator _it, _ite;
// 		int				_nfds, _epollfd, _maxEvents;
// 		epoll_event		_ev, _events[80];
// 		int				isNewClient(int index);
// 		int				responseClient(int fd);
// 	public:
// 		~Webserv();
// 		Webserv();
// 		void	loopingEvent();
// };

class Webserv : public ParseRequest {
	private:
		std::map<std::string, Directive *>	_conf;
		int									_nfds, _epollFd;
		epoll_event							_ev, _events[80];
		int		responseClient(int fd);

	public:
		~Webserv();
		Webserv();

		void	setting(void);
		void	loopingEvent(void);
		friend class ServerHandler;
};

extern Webserv manager;
