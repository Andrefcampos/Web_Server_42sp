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

class Client;
class ServerDirective;

class Webserv : public ParseRequest {
	private:
		std::list<Client *>					_client;
		ServerDirective						*_server_directive;
		int									_nfds, _epollFd;
		epoll_event							_ev, _events[80];
		int		responseClient(Request *request, Client *client);
		void	epoll_CTRL(int clientFd, int event, int flagCTLR, void *ptr);
		void	checkTimeOut();
		void	ereaseClient(Client *client);
		int		removeCliente(Request *request, Client *client);

	public:
		~Webserv();
		Webserv();

		void	setting(void);
		void	loopingEvent(void);
		friend class ServerHandler;
};

extern Webserv manager;
