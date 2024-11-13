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
#include <map>
#include <iostream>
#include "ParserRequest.hpp"

class Handler;

class Webserv: public ParserRequest {
	private:
		std::map<std::string, Directive *>	_conf;
		// std::map<std::string, Server *>::iterator	_it, _ite;
		// int				_nfds, _epollfd, _maxEvents;
		// char			_buffer[8000];
		// epoll_event		_ev, _events[80];
		// int				isNewClient(int index);
		// int				responseClient(int fd, std::string resp);
		// void			createEpoll();
		// void			initServicesAddSocket();

	public:
		~Webserv();
		Webserv();
		// Webserv(std::map<std::string, Server> services);
		// void	loopingEvent();

		friend class Handler;
};

extern Webserv manager;