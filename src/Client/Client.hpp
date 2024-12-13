/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:22:08 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/12 16:32:13 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ctime>

class Server;
class Request;

class Client{
	private:
		Server			*_server;
		Request			*_request;
		std::time_t		_startTime;
		int				_socketFdClient;
		long long int	_maxSize;

	public:
		Client(Server *server, int fdClient);
		~Client();

		Server			*getServer(void) const;
		Request			*getRequest(void) const;
		void			setRequest(Request *request);
		int				getFdClient(void) const;
		void			setMaxSize(long long int maxSize);
		long long int	getMaxSize() const;
		
		int		timeOut(void);
};
