/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:46:49 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/04 18:54:20 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <netinet/in.h>
# include <inttypes.h>


class Socket {
	private:
		sockaddr_in		_addr;
		virtual void	initSocket(int &socketFd);
		virtual void	setSocketReusable(int &socketFd);
		virtual void	setPortReusable(int &socketFd);
		virtual void	setAddr(const in_port_t &port, const in_addr_t &ip);
		virtual void	setAddrToSocket(int &socketFd);
		virtual void	putSocketListeningLimit(int &socketFd, int &events);

	public:
		Socket();
		~Socket();
		virtual int		initTCP(const in_port_t &port, int events, const in_addr_t &ip);
};
