/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateEpoll.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:45:40 by rbutzke           #+#    #+#             */
/*   Updated: 2024/10/03 15:08:18 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATEEPOLL_HPP
#define CREATEEPOLL_HPP

#include <define.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <string>
#include "Socket.hpp"

class CreateEpoll
{
	private:
		int					_nbrFds;
		int					_epollfd;
		int					_nbrCliente;
		char				_buffer[SIZE];
		Socket*				_socketFds;
		struct epoll_event	*_events;
		struct epoll_event	_ev;
		int		initEpoll();
		int		setnonblocking(int sock);
		void	addEpoll(int fd);

	public:
		CreateEpoll(Socket* _socketFds, int nbrCliente);
		~CreateEpoll();
		int getEpoll();
		struct epoll_event *getEpollEvent();
};

#endif