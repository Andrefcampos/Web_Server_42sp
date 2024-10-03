/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:03:49 by andrefil          #+#    #+#             */
/*   Updated: 2024/10/03 10:25:34 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP
# include <netinet/in.h>

class Socket {
	private:
		int					_port, _fd;
		struct sockaddr_in	_peer_addr;
		Socket(void);

	public:
		~Socket(void);
		Socket(int const &port);
		void	bindSocket(void);
		void	setOptSocket(void);
		void	listenSocket(void);
		int		createSocket(void);
		int		getSocket(void) const;
};

#endif
