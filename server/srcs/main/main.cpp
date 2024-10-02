/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:06:57 by andrefil          #+#    #+#             */
/*   Updated: 2024/10/02 18:32:03 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../config/Socket.hpp"
#include <sys/epoll.h>
#include <sys/socket.h>

int	main (void) {

	Socket	socketOne(8080);

	int fdsocket = socketOne.createSocket();
	int	epoolFd = epoll_create1(EPOLL_CLOEXEC);

	struct epoll_event	epollEvent[50], ev;
	ev.data.fd = fdsocket;
	ev.events = EPOLLIN;
	epoll_ctl(epoolFd, EPOLL_CTL_ADD, fdsocket, &ev);
	while (1) {
		int nbFds = epoll_wait(epoolFd, epollEvent, 50,-1);
		for (int i = 0; i < nbFds; ++i) {
			if (epollEvent[i].data.fd == fdsocket) {
				int fdClient = accept(fdsocket, NULL, 0);
				ev.events = EPOLLIN;
				ev.data.fd = fdClient;
				epoll_ctl(epoolFd, EPOLL_CTL_ADD, fdClient, &ev);
			} else {
				char	buffer[1000];
				recv(epollEvent[i].data.fd, buffer, 1000, 0);
			}
		}
	}



	return (0);
}
