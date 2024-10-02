/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefil <andrefil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:03:49 by andrefil          #+#    #+#             */
/*   Updated: 2024/10/02 17:03:22 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP
# include <cstring>
#include <exception>
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdexcept>
# include <iostream>

class Socket {
private:
	int	 _port, _domain, _type, _protocol, _fd;
	struct sockaddr_in	_peer_addr;

	Socket(void);

public:
	~Socket(void) {

	};

	Socket(int const &port) : _port(port), \
		_domain (AF_INET), \
		_type (SOCK_STREAM), \
		_protocol (IPPROTO_TCP) {
		std::memset(&_peer_addr, 0, sizeof(_peer_addr));
		_peer_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		_peer_addr.sin_port = _port;
		_peer_addr.sin_family = _domain;
		_fd = socket(_domain, _type, _protocol);
	};
	// Socket	&operator=(Socket const &param);

	void	bindSocket(void) {
		if (bind(_fd, (struct sockaddr *)&_peer_addr, sizeof(_peer_addr)) ==  -1) {
			throw std::runtime_error("Error: bind");
		}
	};

	void	setOptSocket(void) {
		int i = 1;

		if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int)) == -1) {
			throw std::runtime_error("Error: setsockopt 1");
		}
		if (setsockopt(_fd, SOL_SOCKET, SO_REUSEPORT, &i, sizeof(int)) == -1) {
			throw std::runtime_error("Error: setsockopt 2");
		}
	};

	void	listenSocket(void) {
		if (listen(_fd, 256) == -1) {
			throw std::runtime_error("Error: listen");
		}

	};

	int	createSocket(void) {
		try {
			setOptSocket();
			bindSocket();
			listenSocket();
			return getSocket();
		} catch (const std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
		return 0;
	};

	int		getSocket(void) const {
		return (_fd);
	};
};

#endif
