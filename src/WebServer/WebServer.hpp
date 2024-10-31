/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:19:25 by rbutzke           #+#    #+#             */
/*   Updated: 2024/10/31 12:29:34 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include <sys/epoll.h>
#include <map>
#include <string>
#include <iterator>

class WebService{
	private:
		std::map<std::string, Server>			_services;
		std::map<std::string, Server>::iterator _it, _ite;
		int				_nfds, _epollfd, _maxEvents;
		char			_buffer[8000];
		epoll_event		_ev, _events[80];
		int				isNewClient(int index);
		int				responseClient(int index);
		void			createEpoll();
		void			initEvents();
		void			initServicesAddSocket();

	public:
		~WebService();
		WebService();
		WebService(std::map<std::string, Server> services);
		void	loopingEvent();
};