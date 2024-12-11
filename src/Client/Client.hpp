/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:22:08 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/11 12:39:18 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ctime>

class Server;

class Client{
	private:
		Server		*_server;
		void		*_request;
		std::time_t	_startTime;
		int			_socketFdClient;

	public:
		Client(Server *server, int fdClient);
		~Client();

		Server *getServer(void) const;
		int		getFdClient(void) const;
		void	setRequest(void *request);
		void	*getRequest(void) const;
		int		timeOutRequest(void);
};
