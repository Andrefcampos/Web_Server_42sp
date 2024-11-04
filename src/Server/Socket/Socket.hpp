/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:46:49 by rbutzke           #+#    #+#             */
/*   Updated: 2024/10/23 15:55:36 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <netinet/in.h>

class Socket{
	private:
		sockaddr_in		_addr;
		virtual void	initSocket(int &socketFd);
		virtual void	setSocketReusable(int &socketFd);
		virtual void	setPortReusable(int &socketFd);
		virtual void	setAddr(int socketFd, int &port, const char *ip);
		virtual void	setAddrToSocket(int &socketFd);
		virtual void	putSocketListeningLimit(int &socketFd, int &events);

	public:
		Socket();
		~Socket();
		virtual void	initTCP(int &socketFd, int &port, int &events, const char *ip);
};