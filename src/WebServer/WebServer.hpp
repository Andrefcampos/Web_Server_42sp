/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:19:25 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 18:03:34 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include <sys/epoll.h>
#include <map>
#include <string>
#include <iterator>
#include "ParseRequest.hpp"

class WebService : public ParseRequest{
	private:
		std::map<std::string, Server>			_services;
		std::map<std::string, Server>::iterator _it, _ite;
		int				_nfds, _epollfd, _maxEvents;
		epoll_event		_ev, _events[80];
		int				isNewClient(int index);
		int				responseClient(int fd);
		void			createEpoll();
		void			initServicesAddSocket();
		void			initEpollStruct();
	public:
		~WebService();
		WebService();
		WebService(std::map<std::string, Server> services);
		void	loopingEvent();
		
};