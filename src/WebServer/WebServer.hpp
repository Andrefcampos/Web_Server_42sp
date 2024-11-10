/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefil <andrefil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:19:25 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/08 03:08:45 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include <sys/epoll.h>
#include <map>
#include <string>
#include <iterator>
#include "ParserRequest.hpp"

class WebService: public ParserRequest{
	private:
		std::map<std::string, Server>			_services;
		std::map<std::string, Server>::iterator _it, _ite;
		int				_nfds, _epollfd, _maxEvents;
		epoll_event		_ev, _events[80];
		int				isNewClient(int index);
		int				responseClient(int fd);
		void			createEpoll();
		void			initServicesAddSocket();

	public:
		~WebService();
		WebService();
		WebService(std::map<std::string, Server> services);
		void	loopingEvent();
};
