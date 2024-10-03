/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:06:57 by andrefil          #+#    #+#             */
/*   Updated: 2024/10/03 15:13:28 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include <sys/epoll.h>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include "CreateEpoll.hpp"

int	main (void) {

	Socket	socketOne(8080);
	int		epollfd;
	CreateEpoll	Epoll(&socketOne, 1);
	int fdsocket = socketOne.createSocket();
	int	epoolFd = epoll_create1(EPOLL_CLOEXEC);
	struct epoll_event *epollEvent = Epoll.getEpollEvent();
	struct epoll_event ev;

	while (1) {
		int nbFds = epoll_wait(epoolFd, epollEvent, 50,-1);
		for (int i = 0; i < nbFds; ++i) {
			if (epollEvent[i].data.fd == fdsocket) {
				int fdClient = accept(fdsocket, 0 , 0);
				ev.events = EPOLLIN;
				ev.data.fd = fdClient;
				epoll_ctl(epoolFd, EPOLL_CTL_ADD, fdClient, &ev);
			} else {
				char	buffer[1000];
				recv(epollEvent[i].data.fd, buffer, 1000, 0);
				std::cout << buffer << '\n';
			}
		}
	}



	return (0);
}
